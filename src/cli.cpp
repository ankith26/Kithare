/*
 * This file is a part of the Kithare programming language source code.
 * The source code for Kithare programming language is distributed under the MIT license.
 * Copyright (C) 2021 Kithare Organization
 */

#ifdef _WIN32
#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
#include <codecvt>
#endif

#include <chrono>
#include <clocale>
#include <iostream>

#include <kithare/ansi.hpp>
#include <kithare/file.hpp>
#include <kithare/info.hpp>
#include <kithare/lexer.hpp>
#include <kithare/parser.hpp>
#include <kithare/test.hpp>


using namespace kh;

#define CLI_ERROR_BEGIN() \
    if (!nocolor)         \
        std::cerr << KH_ANSI_FG_RED;

#define CLI_ERROR_END() \
    if (!nocolor)       \
        std::cerr << KH_ANSI_RESET;

static std::vector<std::string> args;
static bool nocolor = false, help = false, show_tokens = false, show_ast = false, show_timer = false,
            silent = false, test_mode = false, version = false;
static std::vector<std::string> excess_args;

static void handleArgs() {
    bool got_file = false;

    for (std::string& _arg : args) {
        std::string arg;

        /* Any arguments after the file name must be forwarded to the program*/
        if (got_file) {
            excess_args.push_back(_arg);
            continue;
        }

        /* Indicates that it is a flag argument (which starts with `-`. `--`, or `/`) */
        if (_arg.size() > 1 && _arg[0] == '-' && _arg[1] == '-') {
            arg = std::string(_arg.begin() + 2, _arg.end());
        }
        else if (_arg.size() > 0 && (_arg[0] == '-' || _arg[0] == '/')) {
            arg = std::string(_arg.begin() + 1, _arg.end());
        }
        else {
            /* Got the file argument */
            got_file = true;
            excess_args.push_back(_arg);
            continue;
        }

        /* Sets the booleans of the specified flags */
        if (arg == "nocolor") {
            nocolor = true;
        }
        else if (arg == "h" || arg == "help") {
            help = true;
        }
        else if (arg == "tokens") {
            show_tokens = true;
        }
        else if (arg == "ast") {
            show_ast = true;
        }
        else if (arg == "t" || arg == "timer") {
            show_timer = true;
        }
        else if (arg == "s" || arg == "silent") {
            silent = true;
        }
        else if (arg == "test") {
            test_mode = true;
        }
        else if (arg == "v" || arg == "version") {
            version = true;
        }
        else {
            if (!silent) {
                CLI_ERROR_BEGIN();
                std::cout << "Unrecognized flag argument: " << arg << '\n';
                CLI_ERROR_END();
            }
            std::exit(1);
        }
    }
}

static int execute() {
    int code = 0;

    if (version && !silent) {
        std::cout << "Kithare " KH_VERSION_STR << "\nOS: " KH_OS << "\nCompiler: " KH_COMPILER
                  << "\nCompiled on " __DATE__ " at " __TIME__ << '\n';
    }

    if (help && !silent) {
        std::cout << "TODO\n";
    }

    /* Unittest */
    if (test_mode) {
        std::vector<std::string> errors;
        kh_test::utf8Test(errors);
        kh_test::lexerTest(errors);
        kh_test::parserTest(errors);

        if (!silent) {
            std::cout << "Unittest: " << errors.size() << " error(s)\n";

            CLI_ERROR_BEGIN();
            for (const std::string& error : errors) {
                std::cerr << error << '\n';
            }
            CLI_ERROR_END();
        }

        std::exit(errors.size());
    }

    /* Compilation */
    if (!excess_args.empty()) {
        std::u32string source;

        try {
            source = fileRead(excess_args[0]);
        }
        catch (Exception& exc) {
            if (!silent) {
                CLI_ERROR_BEGIN();
                std::cerr << exc.format() << '\n';
                CLI_ERROR_END();
            }
            std::exit(1);
        }

        auto lex_start = std::chrono::high_resolution_clock::now();
        std::vector<LexException> lex_exceptions;
        Lexer lexer{source, lex_exceptions};
        std::vector<Token> tokens = lexer.lex();
        auto lex_end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> lex_elapsed = lex_end - lex_start;

        if (show_timer && !silent) {
            std::cout << "Finished lexing in " << lex_elapsed.count() << "s\n";
        }
        if (!lex_exceptions.empty()) {
            if (!silent) {
                CLI_ERROR_BEGIN();
                for (LexException& exc : lex_exceptions) {
                    std::cerr << "LexException: " << exc.format() << '\n';
                }
                CLI_ERROR_END();
            }

            code += lex_exceptions.size();
        }
        if (show_tokens && !silent) {
            std::cout << "tokens:\n";
            for (Token& token : tokens) {
                std::cout << '\t' << strfy(token, true) << '\n';
            }
        }

        auto parse_start = std::chrono::high_resolution_clock::now();
        std::vector<ParseException> parse_exceptions;
        Parser parser{tokens, parse_exceptions};
        AstModule ast = parser.parseWhole();
        auto parse_end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> parse_elapsed = parse_end - parse_start;

        if (show_timer && !silent) {
            std::cout << "Finished parsing in " << parse_elapsed.count() << "s\n";
        }
        if (!parse_exceptions.empty()) {
            if (!silent) {
                CLI_ERROR_BEGIN();
                for (ParseException& exc : parse_exceptions) {
                    std::cerr << "ParseException: " << exc.format() << '\n';
                }
                CLI_ERROR_END();
            }

            code += parse_exceptions.size();
        }
        if (show_ast && !code && !silent) {
            std::cout << strfy(ast) << '\n';
        }
    }

    return code;
}

/* Entry point of the Kithare CLI program */
#ifdef _WIN32
int wmain(const int argc, wchar_t* argv[])
#else
int main(const int argc, char* argv[])
#endif
{
    /* Sets the locale to using UTF-8 */
    std::setlocale(LC_ALL, "en_US.utf8");
#ifdef _WIN32
    /* Sets up std::wcout and std::wcin on Windows */
    std::locale utf8_locale(std::locale(), new std::codecvt_utf8_utf16<wchar_t>);
    std::wcout.imbue(utf8_locale);
    std::wcin.imbue(utf8_locale);

    /* A weird bug, I guess. It enables ANSI escape codes. */
    std::system(" ");
#endif

    args.reserve(argc - 1);

    /* Ignore the first argument */
    for (int arg = 1; arg < argc; arg++) {
#ifdef _WIN32
        args.push_back(strfy(std::wstring(argv[arg])));
#else
        args.push_back(std::string(argv[arg]));
#endif
    }

    handleArgs();
    return execute();
}
