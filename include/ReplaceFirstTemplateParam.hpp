#ifndef REPLACE_FIRST_TEMPLATE_PARAM_HPP_
# define REPLACE_FIRST_TEMPLATE_PARAM_HPP_

namespace traits
{
    template <typename, typename>
    struct ReplaceFirstTemplateParam;

    template <
        template <typename, typename...> class T,
        typename U,
        typename... Args,
        typename V>
    struct ReplaceFirstTemplateParam<T<U, Args...>, V>
    {
        using Type_t = T<V, Args...>;
    };
}

#endif
