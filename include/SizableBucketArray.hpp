#ifndef SIZABLE_BUCKET_ARRAY_HPP_
# define SIZABLE_BUCKET_ARRAY_HPP_

# include <memory>
# include <algorithm>
# include <utility>
# include <type_traits>
# include <sstream>
# include <stdexcept>
# include <cassert>

# include "ReplaceFirstTemplateParam.hpp"

# define assertm(EXPR, MSG) assert((void(MSG), EXPR))

namespace container
{
    template <
        typename T,
        size_t MAX_ELEM_PER_BUCKET = 4,
        typename ElemAlloc = std::allocator<T>>
    class SizableBucketArray
    {
        static_assert(std::is_default_constructible_v<T>,
                      "T must be default constructible");
        static_assert(std::is_copy_constructible_v<T>,
                      "T must be copy constructible");
        static_assert(std::is_copy_assignable_v<T>,
                      "T must be copy assignable");
        static_assert(MAX_ELEM_PER_BUCKET > 0,
                      "MAX_ELEM_PER_BUCKET must be higher than 0");

        using ElemAllocTraits_t = std::allocator_traits<ElemAlloc>;

        /* to allow the copy and move semantic between instances
           of different MAX_ELEM_PER_BUCKET */
        template <typename, size_t, typename>
        friend class SizableBucketArray;

        template <typename>
        class _Iterator;

        template <typename>
        class _ReverseIterator;

    public :
        using Iterator = _Iterator<T>;
        using ConstIterator = _Iterator<const T>;
        using ReverseIterator = _ReverseIterator<T>;
        using ConstReverseIterator = _ReverseIterator<const T>;

        SizableBucketArray() = default;
        SizableBucketArray(const SizableBucketArray&) = default;

        template <size_t MAX_ELEM_PER_BUCKET_OTHER>
        SizableBucketArray(
            const SizableBucketArray<T, MAX_ELEM_PER_BUCKET_OTHER>& other) :
            _buckets(other._buckets)
        { }

        SizableBucketArray(SizableBucketArray&& other) :
            _buckets(std::move(other._buckets))
        { }

        template <size_t MAX_ELEM_PER_BUCKET_OTHER>
        SizableBucketArray(
            SizableBucketArray<T, MAX_ELEM_PER_BUCKET_OTHER>&& other) :
            _buckets(std::move(other._buckets))
        { }

        SizableBucketArray(std::initializer_list<T> initializer)
        {
            onConstructor_setBuckets(initializer.size(),
                                     initializer.begin(),
                                     initializer.end());
        }

        template <typename InputIterator>
        SizableBucketArray(InputIterator begin, InputIterator end)
        {
            onConstructor_setBuckets(std::distance(begin, end),
                                     begin,
                                     end);
        }

        template <typename Container>
        SizableBucketArray(const Container& container)
        {
            onConstructor_setBuckets(std::size(container),
                                     std::cbegin(container),
                                     std::cend(container));
        }

        SizableBucketArray& operator=(const SizableBucketArray&) = default;

        template <size_t MAX_ELEM_PER_BUCKET_OTHER>
        SizableBucketArray& operator=(
            const SizableBucketArray<T, MAX_ELEM_PER_BUCKET_OTHER>& other)
        {
            _buckets = other._buckets;

            return *this;
        }

        SizableBucketArray& operator=(SizableBucketArray&&) = default;

        template <size_t MAX_ELEM_PER_BUCKET_OTHER>
        SizableBucketArray& operator=(
            SizableBucketArray<T, MAX_ELEM_PER_BUCKET_OTHER>&& other)
        {
            _buckets = std::move(other._buckets);

            return *this;
        }

        [[nodiscard]]
        friend inline bool operator==(
            const SizableBucketArray& lhs, const SizableBucketArray& rhs) noexcept
        {
            return lhs._buckets == rhs._buckets;
        }

        [[nodiscard]]
        friend inline bool operator!=(
            const SizableBucketArray& lhs, const SizableBucketArray& rhs) noexcept
        {
            return !(lhs._buckets == rhs._buckets);
        }

        // should be friend but cannot access rhs._buckets
        template <size_t MAX_ELEM_PER_BUCKET_OTHER>
        [[nodiscard]]
        inline bool operator==(
            const SizableBucketArray<T, MAX_ELEM_PER_BUCKET_OTHER>& rhs) const noexcept
        {
            return _buckets == rhs._buckets;
        }

        // should be friend but cannot access rhs._buckets
        template <size_t MAX_ELEM_PER_BUCKET_OTHER>
        [[nodiscard]]
        inline bool operator!=(
            const SizableBucketArray<T, MAX_ELEM_PER_BUCKET_OTHER>& rhs) const noexcept
        {
            return !(*this == rhs);
        }

        [[nodiscard]]
        inline bool empty() const noexcept { return _buckets.totalElemSize == 0; }

        [[nodiscard]]
        inline size_t size() const noexcept { return _buckets.totalElemSize; }

        [[nodiscard]]
        inline size_t capacity() const noexcept { return _buckets.totalElemCapacity; }

        [[nodiscard]]
        inline size_t bucketCount() const noexcept { return _buckets.totalBucketSize; }

        [[nodiscard]]
        size_t bucketSize(size_t index) const
        {
            if (index >= _buckets.totalBucketSize)
            {
                std::ostringstream oss;

                oss << "index (which is "
                    << index
                    << ") >= _buckets.totalBucketSize (which is "
                    << _buckets.totalBucketSize;

                throw std::out_of_range(oss.str());
            }

            return _buckets.buckets[index].size;
        }

        [[nodiscard]]
        const T& at(size_t index) const
        {
            if (index >= _buckets.totalElemSize)
            {
                std::ostringstream oss;

                oss << "index (which is "
                    << index
                    << ") >= _buckets.totalElemSize (which is "
                    << _buckets.totalElemSize;

                throw std::out_of_range(oss.str());
            }

            return _buckets.buckets[Buckets::row(index)].elements[
                Buckets::column(index)];
        }

        [[nodiscard]]
        T& at(size_t index)
        {
            if (index >= _buckets.totalElemSize)
            {
                std::ostringstream oss;

                oss << "index (which is "
                    << index
                    << ") >= _buckets.totalElemSize (which is "
                    << _buckets.totalElemSize;

                throw std::out_of_range(oss.str());
            }

            return _buckets.buckets[Buckets::row(index)]
                .elements[Buckets::column(index)];
        }

        template <typename... Args>
        void emplaceFront(Args&&... args)
        {
            onEmplace_tryAllocateNewBucket();

            ElemAlloc alloc;

            if (_buckets.totalElemSize == 0)
            {
                // call constructor in place with arguments

                // new (&_buckets.buckets[0].elements[0])
                //     T(std::forward<Args>(args)...);
                ElemAllocTraits_t::construct(
                    alloc,
                    &_buckets.buckets[0].elements[0],
                    std::forward<Args>(args)...);
                ++_buckets.buckets[0].size;
            }
            else
            {
                T elementToPutBack = std::move(_buckets.buckets[0].elements[0]);

                // call constructor in place with arguments

                // new (&_buckets.buckets[0].elements[0])
                //     T(std::forward<Args>(args)...);
                ElemAllocTraits_t::construct(
                    alloc,
                    &_buckets.buckets[0].elements[0],
                    std::forward<Args>(args)...);

                uint32_t index = 1;

                for (; index < _buckets.totalElemSize; ++index)
                {
                    std::swap(
                        elementToPutBack,
                        _buckets.buckets[Buckets::row(index)].elements[
                            Buckets::column(index)]);
                }

                _buckets.buckets[Buckets::row(index)].elements[
                    Buckets::column(index)] =
                    std::move(elementToPutBack);
                ++_buckets.buckets[Buckets::row(index)].size;
            }

            ++_buckets.totalElemSize;
        }

        template <typename... Args>
        void emplaceBack(Args&&... args)
        {
            onEmplace_tryAllocateNewBucket();

            // call constructor in place with arguments

            // new (&_buckets.buckets[Buckets::row(_buckets.totalElemSize)].elements[
            //    Buckets::column(_buckets.totalElemSize)])
            //    T(std::forward<Args>(args)...);
            ElemAlloc alloc;

            ElemAllocTraits_t::construct(
                alloc,
                &_buckets.buckets[Buckets::row(_buckets.totalElemSize)].elements[
                    Buckets::column(_buckets.totalElemSize)],
                std::forward<Args>(args)...);
            ++_buckets.buckets[Buckets::row(_buckets.totalElemSize)].size;
            ++_buckets.totalElemSize;
        }

        Iterator erase(ConstIterator position)
        {
            assertm(position._buckets,
                    "position._buckets cannot be null");
            assertm(position._buckets == &_buckets,
                    "position._buckets address isn't the same as _buckets");
            assertm(position._buckets->totalElemSize > 0,
                    "position._buckets->totalElemSize cannot be equal to zero");
            assertm(position._buckets->totalBucketSize > 0,
                    "position._buckets->totalBucketSize cannot be equal to zero");
            assertm(position._buckets->buckets,
                    "position._buckets->buckets cannot be null");

            auto& bucket = _buckets.buckets[Buckets::row(position._index)];

            assertm(bucket.size > 0,
                    "bucket.size cannot be equal to zero");
            assertm(bucket.elements,
                    "bucket.elements cannot be null");

            // call destructor

            // bucket.elements[Buckets::column(position._index)].~T();
            ElemAlloc alloc;

            ElemAllocTraits_t::destroy(
                alloc,
                &bucket.elements[Buckets::column(position._index)]);

            size_t index = position._index;

            for (; index < _buckets.totalElemSize - 1; ++index)
            {
                _buckets.buckets[Buckets::row(index)].elements[
                    Buckets::column(index)] = std::move(
                        _buckets.buckets[Buckets::row(index + 1)].elements[
                            Buckets::column(index + 1)]);
            }

            --_buckets.buckets[Buckets::row(index)].size;
            --_buckets.totalElemSize;

            return Iterator(position._buckets, position._index);
        }

        inline void clear() { _buckets.clear(); }

        [[nodiscard]]
        inline Iterator begin() noexcept
        {
            return Iterator(&_buckets, 0);
        }

        [[nodiscard]]
        inline Iterator end() noexcept
        {
            return Iterator(&_buckets, _buckets.totalElemSize);
        }

        [[nodiscard]]
        inline ConstIterator cbegin() const noexcept
        {
            return ConstIterator(&_buckets, 0);
        }

        [[nodiscard]]
        inline ConstIterator cend() const noexcept
        {
            return ConstIterator(&_buckets, _buckets.totalElemSize);
        }

        [[nodiscard]]
        inline ReverseIterator rbegin() noexcept
        {
            return ReverseIterator(&_buckets, _buckets.totalElemSize - 1);
        }

        [[nodiscard]]
        inline ReverseIterator rend() noexcept
        {
            return ReverseIterator(&_buckets, -1);
        }

        [[nodiscard]]
        inline ConstReverseIterator rcbegin() const noexcept
        {
            return ConstReverseIterator(&_buckets, _buckets.totalElemSize - 1);
        }

        [[nodiscard]]
        inline ConstReverseIterator rcend() const noexcept
        {
            return ConstReverseIterator(&_buckets, -1);
        }

        [[nodiscard]]
        inline static constexpr size_t maxElemPerBucket() noexcept
        {
            return MAX_ELEM_PER_BUCKET;
        }

    private :
        struct Buckets;

        template <typename U>
        class _Iterator
        {
        public :
            using difference_type = std::ptrdiff_t;
            using value_type = U;
            using pointer = U *;
            using reference = U&;
            using iterator_category = std::random_access_iterator_tag;

            _Iterator() = default;
            _Iterator(const _Iterator&) = default;
            _Iterator(_Iterator&&) = default;
            _Iterator& operator=(const _Iterator&) = default;
            _Iterator& operator=(_Iterator&&) = default;

            [[nodiscard]]
            friend inline bool operator==(
                const _Iterator& lhs, const _Iterator& rhs) noexcept
            {
                return lhs._buckets == rhs._buckets && lhs._index == rhs._index;
            }

            [[nodiscard]]
            friend inline bool operator!=(
                const _Iterator& lhs, const _Iterator& rhs) noexcept
            {
                return !(lhs == rhs);
            }

            [[nodiscard]]
            reference operator*()
            {
                assertm(_buckets, "_buckets cannot be null");

                auto& bucket = _buckets->buckets[Buckets::row(_index)];

                assertm(bucket.elements, "bucket.elements cannot be null");

                return bucket.elements[Buckets::column(_index)];
            }

            [[nodiscard]]
            pointer operator->()
            {
                assertm(_buckets, "_buckets cannot be null");

                auto& bucket = _buckets->buckets[Buckets::row(_index)];

                assertm(bucket.elements, "bucket.elements cannot be null");

                return &bucket.elements[Buckets::column(_index)];
            }

            [[nodiscard]]
            reference operator[](difference_type n)
            {
                assertm(_buckets, "_buckets cannot be null");

                auto& bucket = _buckets->buckets[Buckets::row(n)];

                assertm(bucket.elements, "bucket.elements cannot be null");

                return bucket.elements[Buckets::column(n)];
            }

            _Iterator& operator++() noexcept
            {
                ++_index;

                return *this;
            }

            _Iterator operator++(int) noexcept
            {
                _Iterator it(*this);

                operator++();

                return it;
            }

            _Iterator& operator--() noexcept
            {
                --_index;

                return *this;
            }

            _Iterator operator--(int) noexcept
            {
                _Iterator it(*this);

                operator--();

                return it;
            }

            _Iterator& operator+=(difference_type n) noexcept
            {
                _index += n;

                return *this;
            }

            _Iterator& operator-=(difference_type n) noexcept
            {
                _index -= n;

                return *this;
            }

            [[nodiscard]]
            _Iterator operator+(difference_type n) const noexcept
            {
                return _Iterator(_buckets, _index + n);
            }

            [[nodiscard]]
            _Iterator operator-(difference_type n) const noexcept
            {
                return _Iterator(_buckets, _index - n);
            }

            [[nodiscard]]
            operator _Iterator<const U>() const noexcept
            {
                return _Iterator<const U>(_buckets, _index);
            }

        private :
            friend class SizableBucketArray;

            const Buckets *_buckets = nullptr;
            int _index = 0;

            _Iterator(const Buckets *buckets, int index) noexcept :
                _buckets(buckets),
                _index(index)
            { }
        };

        template <typename U>
        class _ReverseIterator
        {
        public :
            using iterator_category = std::random_access_iterator_tag;
            using value_type = U;
            using difference_type = U;
            using pointer = U *;
            using reference = U&;

            _ReverseIterator() = default;
            _ReverseIterator(const _ReverseIterator&) = default;
            _ReverseIterator(_ReverseIterator&&) = default;
            _ReverseIterator& operator=(const _ReverseIterator&) = default;
            _ReverseIterator& operator=(_ReverseIterator&&) = default;

            [[nodiscard]]
            friend inline bool operator==(
                const _ReverseIterator& lhs, const _ReverseIterator& rhs) noexcept
            {
                return lhs._buckets == rhs._buckets && lhs._index == rhs._index;
            }

            [[nodiscard]]
            friend inline bool operator!=(
                const _ReverseIterator& lhs, const _ReverseIterator& rhs) noexcept
            {
                return !(lhs == rhs);
            }

            [[nodiscard]]
            reference operator*()
            {
                assertm(_buckets, "_buckets cannot be null");

                auto& bucket = _buckets->buckets[Buckets::row(_index)];

                assertm(bucket.elements, "bucket.elements cannot be null");

                return bucket.elements[Buckets::column(_index)];
            }

            [[nodiscard]]
            pointer operator->()
            {
                assertm(_buckets, "_buckets cannot be null");

                auto& bucket = _buckets->buckets[Buckets::row(_index)];

                assertm(bucket.elements, "bucket.elements cannot be null");

                return &bucket.elements[Buckets::column(_index)];
            }

            [[nodiscard]]
            reference operator[](difference_type n)
            {
                assertm(_buckets, "_buckets cannot be null");

                auto& bucket = _buckets->buckets[Buckets::row(n)];

                assertm(bucket.elements, "bucket.elements cannot be null");

                return bucket.elements[Buckets::column(n)];
            }

            _ReverseIterator& operator++() noexcept
            {
                --_index;

                return *this;
            }

            _ReverseIterator operator++(int) noexcept
            {
                _ReverseIterator it(*this);

                operator++();

                return it;
            }

            _ReverseIterator& operator--() noexcept
            {
                ++_index;

                return *this;
            }

            _ReverseIterator operator--(int) noexcept
            {
                _ReverseIterator it(*this);

                operator--();

                return it;
            }

            _ReverseIterator& operator+=(difference_type n) noexcept
            {
                _index -= n;

                return *this;
            }

            _ReverseIterator& operator-=(difference_type n) noexcept
            {
                _index += n;

                return *this;
            }

            [[nodiscard]]
            _ReverseIterator operator+(difference_type n) const noexcept
            {
                return _ReverseIterator(_buckets, _index - n);
            }

            [[nodiscard]]
            _ReverseIterator operator-(difference_type n) const noexcept
            {
                return _ReverseIterator(_buckets, _index + n);
            }

            [[nodiscard]]
            operator _ReverseIterator<const U>() const noexcept
            {
                return _ReverseIterator<const U>(_buckets, _index);
            }

        private :
            friend class SizableBucketArray;

            const Buckets *_buckets = nullptr;
            int _index = 0;

            _ReverseIterator(const Buckets *buckets, int index) noexcept :
                _buckets(buckets),
                _index(index)
            { }
        };

        template <typename, typename>
        struct Deleter;

        /* workaround because with operator new[] version without
           the default constructor call, delete[] will segfault
           in ~std::unique_ptr<T[]> if T is not a fundamental type */
        template <typename U, typename AllocTraits>
        struct Deleter<U[], AllocTraits>
        {
            Deleter() = default;
            Deleter(const Deleter&) = delete;

            /* Don't do anything because to avoid pointer copy on _size
               from another instance when move semantic constructor happens
               on unique_ptr<element_type[], Deleter<element_type[]>> */
            Deleter(Deleter&&) noexcept { }

            Deleter& operator=(const Deleter&) = delete;

            /* Don't do anything because to avoid pointer copy on _size
               from another instance when move semantic assignment happens
               on unique_ptr<element_type[], Deleter<element_type[]>> */
            inline Deleter& operator=(Deleter&&) noexcept { return *this; }

            void operator()(U *ptr) const
            {
                assertm(ptr, "ptr cannot be null");
                assertm(_capacity, "_capacity cannot be null");
                assertm(*_capacity, "*_capacity must be higher than 0");
                assertm(_size, "_size cannot be null");

                typename AllocTraits::allocator_type alloc;

                for (auto [ptrCopy, index] =
                         std::make_pair(ptr, uint32_t(0));
                     index < *_size;
                     ++ptrCopy, ++index)
                 {
                     // call destructor

                     // ptrCopy->~U();
                     AllocTraits::destroy(alloc, ptrCopy);
                 }

                // operator delete[](ptr, sizeof(U) * *_capacity);
                AllocTraits::deallocate(alloc, ptr, *_capacity);
            }

            /* need to call this function for each constructor to init
               std::unique_ptr<element_type[], Deleter<element_type[]>>
               with the right capacity to delete correctly in Deleter */
            inline void setCapacity(const size_t *capacity) noexcept
            {
                _capacity = capacity;
            }

            /* need to call this function for each constructor to
               call the right number of element destructor */
            inline void setSize(const size_t *size) noexcept
            {
                _size = size;
            }

        private :
            const size_t *_capacity = nullptr;
            const size_t *_size = nullptr;
        };

        /* Use std::unique_ptr rather than std::vector to manage manually
           the allocation/deallocation and construct/destroy */
        struct Buckets
        {
            struct Bucket
            {
                using Deleter_t = Deleter<T[], ElemAllocTraits_t>;

                size_t capacity = 0;
                size_t size = 0;
                std::unique_ptr<T[], Deleter_t> elements;

                Bucket()
                {
                    onConstructor_initDeleter();
                    allocateElements();
                }

                ~Bucket() = default;

                Bucket(const Bucket& other)
                {
                    onConstructor_initDeleter();
                    allocateElements();

                    for (auto [alloc, index] =
                             std::make_pair(ElemAlloc(), uint32_t(0));
                         index < other.size;
                         ++index)
                    {
                        // call copy constructor

                        // new (data) T(other.elements[index]);
                        ElemAllocTraits_t::construct(
                            alloc, &elements[index], other.elements[index]);
                    }

                    size = other.size;
                }

                template <typename U>
                Bucket(const U& buckets, uint32_t& index)
                {
                    onConstructor_initDeleter();
                    allocateElements();

                    uint32_t index2 = 0;

                    for (ElemAlloc alloc;
                         index2 < capacity && index < buckets.totalElemSize;
                         ++index2, ++index)
                    {
                        /* call copy constructor, but use the row() and column()
                           functions of the other instance to get the
                           right element index */

                        // new (data) T(buckets.buckets[buckets.row(index)].elements[
                        //     buckets.column(index)]);
                        ElemAllocTraits_t::construct(
                            alloc,
                            &elements[index2],
                            buckets.buckets[buckets.row(index)].elements[
                                buckets.column(index)]);
                    }

                    size = index2;
                }

                Bucket(Bucket&& other) :
                    capacity(std::exchange(other.capacity, 0)),
                    size(std::exchange(other.size, 0)),
                    elements(std::move(other.elements))
                {
                    onConstructor_initDeleter();
                }

                template <typename U>
                Bucket(U&& buckets, uint32_t& index)
                {
                    onConstructor_initDeleter();
                    allocateElements();

                    uint32_t index2 = 0;

                    for (ElemAlloc alloc;
                         index2 < capacity && index < buckets.totalElemSize;
                         ++index2, ++index)
                    {
                        /* call move constructor, but use the row() and column()
                           functions of the other instance to get the
                           right element index */

                        // new (data) T(std::move(
                        //     buckets.buckets[buckets.row(index)].elements[
                        //         buckets.column(index)]));
                        ElemAllocTraits_t::construct(
                            alloc,
                            &elements[index2],
                            std::move(buckets.buckets[buckets.row(index)].elements[
                                buckets.column(index)]));
                    }

                    size = index2;
                }

                Bucket& operator=(const Bucket& other)
                {
                    if (this != &other)
                    {
                        if (size < other.size)
                        {
                            for (auto [alloc, index] =
                                     std::make_pair(ElemAlloc(), uint32_t(size));
                                 index < other.size;
                                 ++index)
                            {
                                // call default constructor
                                ElemAllocTraits_t::construct(
                                    alloc,
                                    &elements[index]);
                            }

                            for (auto [alloc, index] =
                                     std::make_pair(ElemAlloc(), uint32_t(0));
                                 index < other.size;
                                 ++index)
                            {
                                // call copy assignment
                                elements[index] = other.elements[index];
                            }
                        }
                        else
                        {
                            uint32_t index = 0;

                            for (;index < other.size && index < size; ++index)
                            {
                                // call copy assignment
                                elements[index] = other.elements[index];
                            }

                            for (ElemAlloc alloc; index < size; ++index)
                            {
                                // call destructor
                                ElemAllocTraits_t::destroy(
                                    alloc, &elements[index]);
                            }
                        }

                        size = other.size;
                    }

                    return *this;
                }

                Bucket& operator=(Bucket&& other)
                {
                    if (this != &other)
                    {
                        capacity = std::exchange(other.capacity, 0);
                        size = std::exchange(other.size, 0);
                        elements = std::move(other.elements);
                    }

                    return *this;
                }

                [[nodiscard]]
                friend bool operator==(const Bucket& lhs, const Bucket& rhs) noexcept
                {
                    if (lhs.size != rhs.size)
                    {
                        return false;
                    }

                    if (lhs.size == 0)
                    {
                        return true;
                    }

                    for (uint32_t index = 0; index < lhs.size; ++index)
                    {
                        if (lhs.elements[index] != rhs.elements[index])
                        {
                            return false;
                        }
                    }

                    return true;
                }

                [[nodiscard]]
                friend inline bool operator!=(const Bucket& lhs, const Bucket& rhs) noexcept
                {
                    return !(lhs == rhs);
                }

                template <typename U>
                void copyAssignmentFrom(const U& buckets, uint32_t& index)
                {
                    const size_t nbElemToCopy =
                        std::min(buckets.totalElemSize - index, MAX_ELEM_PER_BUCKET);
                    uint32_t index2 = 0;

                    if (size < nbElemToCopy)
                    {
                        for (auto [alloc, index3] =
                                 std::make_pair(ElemAlloc(), uint32_t(size));
                             index3 < nbElemToCopy;
                             ++index3)
                        {
                            // call default constructor
                            ElemAllocTraits_t::construct(
                                alloc,
                                &elements[index3]);
                        }

                        for (ElemAlloc alloc;
                             index2 < capacity && index < buckets.totalElemSize;
                             ++index2, ++index)
                        {
                            /* call copy assignment, but use the row() and column()
                               functions of the other instance to get the
                               right element index */
                            elements[index2] = buckets.buckets[buckets.row(index)]
                                .elements[buckets.column(index)];
                        }
                    }
                    else
                    {
                        for (; index2 < capacity && index < buckets.totalElemSize;
                             ++index2, ++index)
                        {
                            /* call copy assignment, but use the row() and column()
                               functions of the other instance to get the
                               right element index */
                            elements[index2] = buckets.buckets[buckets.row(index)]
                                .elements[buckets.column(index)];
                        }

                        for (auto [alloc, index3] =
                                 std::make_pair(ElemAlloc(), index2);
                             index3 < size;
                             ++index3)
                        {
                            // call destructor
                            ElemAllocTraits_t::destroy(alloc, &elements[index3]);
                        }
                    }

                    size = index2;
                }

                template <typename U>
                void moveAssignmentFrom(U&& buckets, uint32_t& index)
                {
                    const size_t nbElemToCopy =
                        std::min(buckets.totalElemSize - index, MAX_ELEM_PER_BUCKET);
                    uint32_t index2 = 0;

                    if (size < nbElemToCopy)
                    {
                        for (auto [alloc, index3] =
                                 std::make_pair(ElemAlloc(), uint32_t(size));
                             index3 < nbElemToCopy;
                             ++index3)
                        {
                            // call default constructor
                            ElemAllocTraits_t::construct(
                                alloc,
                                &elements[index3]);
                        }

                        for (ElemAlloc alloc;
                             index2 < capacity && index < buckets.totalElemSize;
                             ++index2, ++index)
                        {
                            /* call move assignment, but use the row() and column()
                               functions of the other instance to get the
                               right element index */
                            elements[index2] =
                                std::move(buckets.buckets[buckets.row(index)].elements[
                                    buckets.column(index)]);
                        }
                    }
                    else
                    {
                        for (ElemAlloc alloc;
                             index2 < capacity && index < buckets.totalElemSize;
                             ++index2, ++index)
                        {
                            /* call move assignment, but use the row() and column()
                               functions of the other instance to get the
                               right element index */
                            elements[index2] =
                                std::move(buckets.buckets[buckets.row(index)].elements[
                                    buckets.column(index)]);
                        }

                        for (auto [alloc, index3] =
                                 std::make_pair(ElemAlloc(), index2);
                             index3 < size;
                             ++index3)
                        {
                            // call destructor
                            ElemAllocTraits_t::destroy(alloc, &elements[index3]);
                        }
                    }

                    size = index2;
                }

                // clear doesn't reset the bucket capacity
                void clear()
                {
                    for (auto [alloc, index] =
                             std::make_pair(ElemAlloc(), uint32_t(0));
                         index < size; ++index)
                    {
                        ElemAllocTraits_t::destroy(
                            alloc,
                            &elements[index]);
                    }

                    size = 0;
                }

                [[nodiscard]]
                inline static constexpr size_t nbElemToAllocate() noexcept
                {
                    return MAX_ELEM_PER_BUCKET;
                }

            private :
                void onConstructor_initDeleter() noexcept
                {
                    auto& deleter = elements.get_deleter();

                    deleter.setCapacity(&capacity);
                    deleter.setSize(&size);
                }

                void allocateElements()
                {
                    constexpr size_t NB_ELEM_TO_ALLOCATE = nbElemToAllocate();

                    /* avoid the default constructor call for each
                       element with std::make_unique */

                    // T *data = static_cast<T *>(operator new[](
                    //     sizeof(T) * NB_ELEM_TO_ALLOCATE, std::nothrow));
                    ElemAlloc alloc;
                    T *data = ElemAllocTraits_t::allocate(
                        alloc, NB_ELEM_TO_ALLOCATE);

                    elements.reset(data);
                    capacity = NB_ELEM_TO_ALLOCATE;
                }
            };

            using BucketAlloc_t =
                typename traits::ReplaceFirstTemplateParam<
                    ElemAlloc, Bucket>::Type_t;
            using BucketAllocTraits_t =
                std::allocator_traits<BucketAlloc_t>;
            using Deleter_t =
                Deleter<Bucket[], BucketAllocTraits_t>;

            size_t totalElemCapacity = 0;
            size_t totalElemSize = 0;
            size_t totalBucketSize = 0;
            std::unique_ptr<Bucket[], Deleter_t> buckets;

            Buckets() noexcept { onConstructor_initDeleter(); }
            ~Buckets() = default;

            Buckets(const Buckets& other)
            {
                onConstructor_initDeleter();

                // avoid to allocate zero-length array if other.totalElemSize == 0
                if (other.totalElemSize == 0)
                {
                    return;
                }

                allocateBucketsFrom(other.totalElemSize);

                for (auto [alloc, index] =
                         std::make_pair(BucketAlloc_t(), uint32_t(0));
                     index < totalBucketSize;
                     ++index)
                {
                    // call copy constructor
                    BucketAllocTraits_t::construct(
                        alloc,
                        &buckets[index],
                        other.buckets[index]);
                }

                totalElemSize = other.totalElemSize;
            }

            template <typename U>
            Buckets(const U& other)
            {
                onConstructor_initDeleter();

                // avoid to allocate zero-length array if other.totalElemSize == 0
                if (other.totalElemSize == 0)
                {
                    return;
                }

                allocateBucketsFrom(other.totalElemSize);

                for (auto [alloc, index, index2] =
                         std::make_tuple(BucketAlloc_t(), uint32_t(0), uint32_t(0));
                     index < totalBucketSize && index2 < other.totalElemSize;
                     ++index)
                {
                    // call copy constructor
                    BucketAllocTraits_t::construct(
                        alloc,
                        &buckets[index],
                        other,
                        index2);
                }

                totalElemSize = other.totalElemSize;
            }

            Buckets(Buckets&& other) :
                totalElemCapacity(std::exchange(other.totalElemCapacity, 0)),
                totalElemSize(std::exchange(other.totalElemSize, 0)),
                totalBucketSize(std::exchange(other.totalBucketSize, 0)),
                buckets(std::move(other.buckets))
            {
                onConstructor_initDeleter();
            }

            template <typename U>
            Buckets(U&& other)
            {
                onConstructor_initDeleter();

                // avoid to allocate zero-length array if other.totalElemSize == 0
                if (other.totalElemSize == 0)
                {
                    return;
                }

                allocateBucketsFrom(other.totalElemSize);

                for (auto [alloc, index, index2] =
                         std::make_tuple(BucketAlloc_t(), uint32_t(0), uint32_t(0));
                     index < totalBucketSize && index2 < other.totalElemSize;
                     ++index)
                {
                    // call move constructor
                    BucketAllocTraits_t::construct(
                        alloc,
                        &buckets[index],
                        std::forward<U>(other),
                        index2);
                }

                other.buckets.reset();
                other.totalBucketSize = 0;
                totalElemSize = std::exchange(other.totalElemSize, 0);
                other.totalElemCapacity = 0;
            }

            Buckets& operator=(const Buckets& other)
            {
                if (this != &other)
                {
                    if (totalElemCapacity < other.totalElemSize)
                    {
                        allocateBucketsFrom(other.totalElemSize);

                        for (auto [alloc, index] =
                                 std::make_pair(BucketAlloc_t(), uint32_t(0));
                             index < totalBucketSize;
                             ++index)
                        {
                            // call default constructor
                            BucketAllocTraits_t::construct(
                                alloc,
                                &buckets[index]);
                        }
                    }

                    uint32_t index = 0;

                    for (const size_t nbBucketCurrentlyUsedFromOther =
                             nbBucketFrom(other.totalElemSize);
                         index < nbBucketCurrentlyUsedFromOther;
                         ++index)
                    {
                        // call copy assignment
                        buckets[index] = other.buckets[index];
                    }

                    for (const size_t nbBucketCurrentlyUsed =
                             nbBucketFrom(totalElemSize);
                         index < nbBucketCurrentlyUsed;
                         ++index)
                    {
                        buckets[index].clear();
                    }

                    totalElemSize = other.totalElemSize;
                }

                return *this;
            }

            template <typename U>
            Buckets& operator=(const U& other)
            {
                if (totalElemCapacity < other.totalElemSize)
                {
                    allocateBucketsFrom(other.totalElemSize);

                    for (auto [alloc, index] =
                             std::make_pair(BucketAlloc_t(), uint32_t(0));
                         index < totalBucketSize;
                         ++index)
                    {
                        // call default constructor
                        BucketAllocTraits_t::construct(
                            alloc,
                            &buckets[index]);
                    }
                }

                uint32_t index = 0;

                for (uint32_t index2 = 0;
                     index < totalBucketSize && index2 < other.totalElemSize;
                     ++index)
                {
                    buckets[index].copyAssignmentFrom(other, index2);
                }

                for (const size_t nbBucketCurrentlyUsed =
                         nbBucketFrom(totalElemSize);
                     index < nbBucketCurrentlyUsed;
                     ++index)
                {
                    buckets[index].clear();
                }

                totalElemSize = other.totalElemSize;

                return *this;
            }

            Buckets& operator=(Buckets&& other)
            {
                if (this != &other)
                {
                    buckets = std::move(other.buckets);
                    totalBucketSize = std::exchange(other.totalBucketSize, 0);
                    totalElemSize = std::exchange(other.totalElemSize, 0);
                    totalElemCapacity = std::exchange(other.totalElemCapacity, 0);
                }

                return *this;
            }

            template <typename U>
            Buckets& operator=(U&& other)
            {
                if (totalElemCapacity < other.totalElemSize)
                {
                    allocateBucketsFrom(other.totalElemSize);

                    for (auto [alloc, index] =
                             std::make_pair(BucketAlloc_t(), uint32_t(0));
                         index < totalBucketSize;
                         ++index)
                    {
                        // call default constructor
                        BucketAllocTraits_t::construct(
                            alloc,
                            &buckets[index]);
                    }
                }

                uint32_t index = 0;

                for (uint32_t index2 = 0;
                     index < totalBucketSize && index2 < other.totalElemSize;
                     ++index)
                {
                    buckets[index].moveAssignmentFrom(std::forward<U>(other), index2);
                }

                for (const size_t nbBucketCurrentlyUsed =
                         nbBucketFrom(totalElemSize);
                     index < nbBucketCurrentlyUsed;
                     ++index)
                {
                    buckets[index].clear();
                }

                other.buckets.reset();
                other.totalBucketSize = 0;
                totalElemSize = std::exchange(other.totalElemSize, 0);
                other.totalElemCapacity = 0;

                return *this;
            }

            [[nodiscard]]
            friend bool operator==(const Buckets& lhs, const Buckets& rhs) noexcept
            {
                if (lhs.totalElemSize != rhs.totalElemSize)
                {
                    return false;
                }

                if (lhs.totalElemSize == 0)
                {
                    return true;
                }

                for (uint32_t index = 0;
                     index < lhs.totalBucketSize && index < rhs.totalBucketSize;
                     ++index)
                {
                    if (lhs.buckets[index] != rhs.buckets[index])
                    {
                        return false;
                    }
                }

                return true;
            }

            [[nodiscard]]
            friend inline bool operator!=(const Buckets& lhs, const Buckets& rhs) noexcept
            {
                return !(lhs == rhs);
            }

            template <typename U>
            [[nodiscard]]
            friend bool operator==(const Buckets& lhs, const U& rhs) noexcept
            {
                if (lhs.totalElemSize != rhs.totalElemSize)
                {
                    return false;
                }

                if (lhs.totalElemSize == 0)
                {
                    return true;
                }

                for (uint32_t index = 0; index < lhs.totalElemSize; ++index)
                {
                    // use the row() and column() functions related to each instance
                    if (lhs.buckets[row(index)].elements[column(index)]
                        != rhs.buckets[rhs.row(index)].elements[rhs.column(index)])
                    {
                        return false;
                    }
                }

                return true;
            }

            template <typename U>
            [[nodiscard]]
            friend inline bool operator!=(const Buckets& lhs, const U& rhs) noexcept
            {
                return !(lhs == rhs);
            }

            // clear doesn't reset buckets capacity
            void clear()
            {
                for (uint32_t index = 0; index < totalBucketSize; ++index)
                {
                    buckets[index].clear();
                }

                totalElemSize = 0;
            }

            void allocateBucketsFrom(const size_t size)
            {
                assertm(size > 0, "cannot allocate zero-length bucket array");

                const size_t nbBucketToAllocate = nbBucketFrom(size);

                // Bucket *data = static_cast<Bucket *>(operator new[](
                //     sizeof(Bucket) * nbBucketToAllocate, std::nothrow));
                BucketAlloc_t alloc;
                Bucket *data = BucketAllocTraits_t::allocate(
                    alloc, nbBucketToAllocate);

                buckets.reset(data);

                totalBucketSize = nbBucketToAllocate;
                totalElemSize = 0;
                totalElemCapacity = nbBucketToAllocate * Bucket::nbElemToAllocate();
            }

            [[nodiscard]]
            inline static constexpr size_t nbBucketFrom(const size_t size) noexcept
            {
                return (size > 0) ? ((size - 1) / MAX_ELEM_PER_BUCKET) + 1 : 0;
            }

            [[nodiscard]]
            inline static constexpr size_t row(const size_t index) noexcept
            {
                return index / MAX_ELEM_PER_BUCKET;
            }

            [[nodiscard]]
            inline static constexpr size_t column(const size_t index) noexcept
            {
                return index % MAX_ELEM_PER_BUCKET;
            }

        private :
            void onConstructor_initDeleter() noexcept
            {
                auto& deleter = buckets.get_deleter();

                deleter.setCapacity(&totalBucketSize);
                deleter.setSize(&totalBucketSize);
            }
        };

        Buckets _buckets;

        template <typename InputIterator>
        void onConstructor_setBuckets(
            const size_t size, InputIterator begin, InputIterator end)
        {
            // avoid to allocate zero-length array if size == 0
            if (size == 0)
            {
                return;
            }

            _buckets.allocateBucketsFrom(size);

            for (auto [alloc, index] =
                     std::make_pair(
                         typename Buckets::BucketAlloc_t(), uint32_t(0));
                 index < _buckets.totalBucketSize;
                 ++index)
            {
                // call default constructor
                Buckets::BucketAllocTraits_t::construct(
                    alloc, &_buckets.buckets[index]);
            }

            for (auto [alloc, index] =
                     std::make_pair(ElemAlloc(), uint32_t(0));
                 begin != end;
                 ++begin, ++index)
            {
                // new (&_buckets.buckets[Buckets::row(index)].elements[
                //     Buckets::column(index)])
                //     T(*begin);
                ElemAllocTraits_t::construct(
                    alloc,
                    &_buckets.buckets[Buckets::row(index)].elements[
                         Buckets::column(index)],
                    *begin);
                ++_buckets.buckets[Buckets::row(index)].size;
                ++_buckets.totalElemSize;
            }
        }

        void onEmplace_tryAllocateNewBucket()
        {
            if (_buckets.totalElemSize < _buckets.totalElemCapacity)
            {
                return;
            }

            auto tmpBuckets = std::move(_buckets);

            _buckets.allocateBucketsFrom(tmpBuckets.totalElemSize + 1);

            for (auto [alloc, index] =
                     std::make_pair(
                         typename Buckets::BucketAlloc_t(), uint32_t(0));
                 index < _buckets.totalBucketSize;
                 ++index)
            {
                // call default constructor
                Buckets::BucketAllocTraits_t::construct(
                    alloc, &_buckets.buckets[index]);
            }

            if (tmpBuckets.buckets)
            {
                auto tmpBucketsData = tmpBuckets.buckets.get();

                std::move(tmpBucketsData,
                          tmpBucketsData + tmpBuckets.totalBucketSize,
                          _buckets.buckets.get());
            }

            _buckets.totalElemSize = tmpBuckets.totalElemSize;
        }
    };
}

#endif
