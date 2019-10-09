#ifndef env_arguments_h
#define env_arguments_h 1

#include <algorithm>
#include <string>
#include <string_view>
#include <vector>

namespace env {

//class cl_argument_t;
//auto make_cl_argument(std::string line) -> cl_argument_t;

/*class cl_argument_t {
    std::string arg;
    std::string val;

   public:
    cl_argument_t() = default;
    cl_argument_t(std::string arg, std::string val) : arg{arg}, val{val} {}

    std::string get() { return val; }

    bool operator==(const std::string& n) const { return n == arg; }

    friend cl_argument_t make_cl_argument(std::string line) {
        auto pos = line.find('=');
        return pos != std::string::npos
                   ? cl_argument_t{line.substr(0, pos), line.substr(pos + 1)}
                   : cl_argument_t{};
    }
};  // class cl_argument_c

class cl_arguments_t;
auto make_cl_arguments(int, char* []) -> cl_arguments_t;
*/

class scoped_arguments;

class arguments {

    using args_t = std::vector<std::string>;
    using prog_t = typename args_t::const_iterator;
    using pref_t = std::string;

    args_t args { };
    prog_t prog { };
    pref_t pref { };

public:
    constexpr arguments() = default;
    ~arguments() noexcept = default;

    arguments(const arguments& o) = default;
    arguments& operator=(const arguments& o) = default;

    arguments(arguments&& o) noexcept = default;
    arguments& operator=(arguments&& o) noexcept = default;

    arguments(args_t&& args, pref_t&& pref)
        : args { std::move(args)  }
        , prog { std::begin(args) }
        , pref { std::move(pref)  } {
    }

    arguments(args_t&& args)
        : arguments { std::move(args), "" } {
    }

    operator bool() const { return std::begin(args) != std::end(args); }

    scoped_arguments get(std::string_view prefix); 
}; // class arguments

class scoped_arguments {
    using args_type = std::vector<std::string>;
    using delm_type = std::string;

    args_type args = {     };
    delm_type delm = { "=" };

public:
    scoped_arguments(const args_type& args)
        : args { args } {
    }

    operator bool() const { return std::begin(args) != std::end(args); }

    auto get(std::string_view a) {
        auto it = std::find(begin(args), end(args), a);
        return it != std::end(args) ? *it : "";
    }
}; // class scoped_arguments

scoped_arguments arguments::get(std::string_view scope) {
    auto prefix = pref + std::string { scope };
    auto it = std::partition(std::begin(args), std::end(args),
            [&](auto&& arg) {
                return arg.find(prefix) != 0;
            });
//    args_type res(std::distance(it, std::end(args)));
//    std::transform(it, std::end(args), it/*std::begin(res)*/,
//            [&](auto&& arg) {
//                return arg.substr(prefix.size());
//            });
    args_t res { it, std::transform(it, std::end(args), it,
            [&](auto&& arg) {
                return arg.substr(prefix.size());
            })};
//    std::move(it, std::end(args), std::back_inserter(res));
    args.erase(it, std::end(args));
    return scoped_arguments { res };
}

}  // namespace env

#endif
