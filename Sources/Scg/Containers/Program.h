/**
 * @file Scg/Containers/Program.h
 *
 * @copyright Copyright (C) 2014 Rafid Khalid Abdullah
 *
 * @license This file is released under Alusus Public License, Version 1.0.
 * For details on usage and copying conditions read the full license in the
 * accompanying license file or at <http://alusus.net/alusus_license_1_0>.
 */
//==============================================================================

#ifndef __Program_h__
#define __Program_h__

// STL header files
#include <list>

// Alusus header files
#include <typedefs.h>
#include <llvm_fwd.h>

// Scg forward declarations
// TODO: Maybe this should be moved to an fwd file?
namespace Scg
{
class ArrayType;
class BinaryOperator;
class Block;
class FloatConst;
class CallFunction;
class DefineFunction;
class PointerType;
class Return;
}

namespace Scg
{
class Program
{
  /*! A list of the modules making up this program. */
  ModuleArray modules;

public:
  /**
   * Class constructor.
   */
  Program() {}

  /**
   * Class destructor.
   */
  ~Program()
  {
    for (auto module : this->modules) {
      delete module;
    }
    this->modules.clear();
  }

public:
  const ModuleArray &GetModules() const { return modules; }
  ModuleArray &GetModules() { return modules; }

  /**
   * Adds the given module to the program.
   * @param[in] module  A pointer to the module to be added. Notice that this
   *                    should be allocated in the heap and is going to be
   *                    freed by the program so the user shouldn't free it.
   */
  void AddModule(Module *module)
  {
    this->modules.push_back(module);
  }

  /**
   * Finds the DefineFunction instructions that generates functions matching
   * the given name.
   * @return An array containing all the matching DefineFunction instructions.
   */
  std::vector<DefineFunction*> FindDefineFunction(const std::string &funcName,
      const ValueTypeSpecArray &arguments);

  /**
   * Finds the DeclareExtFunction instructions that generates functions matching
   * the given name.
   * @return An array containing all the matching DeclareExtFunction instructions.
   */
  std::vector<DeclareExtFunction*> FindDeclareFunction(const std::string &funcName,
      const ValueTypeSpecArray &arguments);

  /**
   * Compiles the program into LLVM IR and return the result.
   * @return A string containing the generated LLVM IR code.
   */
  std::string Compile();

  /**
   * Executes the program given the name of the main function.
   * @param[in] functionName  The name of the entry point of the program.
   */
  void Execute(const char *functionName);
};
}

#endif // __Program_h__