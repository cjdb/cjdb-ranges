namespace cjdb {
   namespace detail_get_while_fn {
      struct get_while_fn {
         template<Character CharT, class Traits, Predicate<CharT> F>
         std::basic_string<CharT, Traits>
         operator()(std::basic_istream<CharT, Traits>& in, F f) const noexcept
         {
            using namespace ranges;
            return 
         }
      };
   } // detail_get_while_fn

   /// \brief Reads UTF-8 code units until some predicate is satisfied.
   /// \param in A reference to a UTF-8-compatible istream object.
   /// \param f A unary predicate to apply to the input.
   /// \returns A UTF-8 string containing the characters read in.
   /// \note skip_code_units skips whitespace by default. It is the responsibility of the user to
   ///       first call `in.set(std::ios_base::skipws)`.
   /// \note skip_code_units is a niebloid. This means that:
   ///      * explicit template arguments may not be specified when calling skip_code_units.
   ///      * skip_code_units cannot be found by argument-dependent lookup (ADL).
   ///      * when skip_code_units is found by normal unqualified lookup, it inhibits ADL.
   ///
   inline constexpr auto get_while = detail_get_while_fn::get_while_fn{};
} // namespace cjdb