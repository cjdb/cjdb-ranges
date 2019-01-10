
struct unwrap_fn {
   template<class T>
   constexpr T operator()(std::optional<T>& t) noexcept
   // [[expects: t != nullopt]]
   {
      Expects(t != std::nullopt);
      return std::move(*t);
   }

   template<class T>
   constexpr T operator()(std::optional<T>&& t) noexcept
   {
      Expects(t != std::nullopt);
      return std::move(*std::move(t));
   }
};