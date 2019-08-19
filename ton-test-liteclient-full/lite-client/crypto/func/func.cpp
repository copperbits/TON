#include "func.h"
#include "parser/srcread.h"
#include "parser/lexer.h"
#include "parser/symtable.h"
#include <getopt.h>

namespace funC {

/*
 * 
 *   OUTPUT CODE GENERATOR
 * 
 */

void generate_output_func(SymDef* func_sym) {
  SymValCodeFunc* func_val = dynamic_cast<SymValCodeFunc*>(func_sym->value);
  assert(func_val);
  std::string name = sym::symbols.get_name(func_sym->sym_idx);
  std::cerr << "\n\n=========================\nfunction " << name << " : " << func_val->get_type() << std::endl;
  if (!func_val->code) {
    std::cerr << "( undefined )\n";
  } else {
    CodeBlob& code = *(func_val->code);
    code.print(std::cerr, 9);
    code.simplify_var_types();
    // std::cerr << "after simplify_var_types: \n";  code.print(std::cerr, 0);
    code.prune_unreachable_code();
    // std::cerr << "after prune_unreachable: \n";  code.print(std::cerr, 0);
    code.split_vars(true);
    // std::cerr << "after split_vars: \n";  code.print(std::cerr, 0);
    for (int i = 0; i < 8; i++) {
      code.compute_used_code_vars();
      // std::cerr << "after compute_used_vars: \n";  code.print(std::cerr, 6);
      code.fwd_analyze();
      // std::cerr << "after fwd_analyze: \n";  code.print(std::cerr, 6);
      code.prune_unreachable_code();
      // std::cerr << "after prune_unreachable: \n";  code.print(std::cerr, 6);
    }
    code.mark_noreturn();
    code.print(std::cerr, 15);
    std::cerr << "\n---------- resulting code for " << name << " -------------\n";
    code.generate_code(std::cout, Stack::_StkCmt | Stack::_CptStkCmt);
    std::cerr << "--------------\n";
  }
}

int generate_output() {
  int errors = 0;
  for (SymDef* func_sym : glob_func) {
    try {
      generate_output_func(func_sym);
    } catch (src::Error& err) {
      std::cerr << "cannot generate code for function `" << sym::symbols.get_name(func_sym->sym_idx) << "`:\n"
                << err << std::endl;
      ++errors;
    }
  }
  return errors;
}

}  // namespace funC

void usage(const char* progname) {
  std::cerr << "usage: " << progname << " [-i] [-o<output-filename>] {<func-source-filename> ...}\n";
  std::exit(2);
}

std::string output_filename;

int main(int argc, char* const argv[]) {
  int i;
  bool interactive = false;
  while ((i = getopt(argc, argv, "hio:")) != -1) {
    switch (i) {
      case 'i':
        interactive = true;
        break;
      case 'o':
        output_filename = optarg;
        break;
      case 'h':
      default:
        usage(argv[0]);
    }
  }

  funC::define_keywords();
  funC::define_builtins();

  int ok = 0, proc = 0;
  try {
    while (optind < argc) {
      ok += funC::parse_source_file(argv[optind++]);
      proc++;
    }
    if (interactive) {
      ok += funC::parse_source_stdin();
      proc++;
    }
    if (ok < proc) {
      throw src::Fatal{"output code generation omitted because of errors"};
    }
    if (!proc) {
      throw src::Fatal{"no source files, no output"};
    }
    funC::generate_output();
  } catch (src::Fatal& fatal) {
    std::cerr << "fatal: " << fatal << std::endl;
    std::exit(1);
  } catch (src::Error& error) {
    std::cerr << error << std::endl;
    std::exit(1);
  } catch (funC::UniformizeError& unif_err) {
    std::cerr << "fatal: ";
    unif_err.print_message(std::cerr);
    std::cerr << std::endl;
    std::exit(1);
  }
}
