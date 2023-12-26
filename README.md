# Serial

Serialize/Deserialize user defined data structures of native types and `stl` containers 
in a few simple steps with minial lines of code.
1. Obtain Data object
1. Obtain C++ Stream object
1. Select Format and Read/Write Data using Stream 

```
using namespace std;
using namespace serial;

auto data = map<string, vector<map<int, set<float>>>>();

stringstream s;

Write(format::TYPE::TEXT, data, s);

Read(format::TYPE::TEXT, data, s); 
```

## Overview

* Simple approach to describe data structure, supporting POD and user defined classes
* Out of box support of common `stl` containers and easily extended for other containers
* Copyless design to prevent unnecessary overhead
* Data structure definition is decoupled from file format logic
  * basic formats provided
  * easily extended for additional formats


## Examples

# Coding Standard
* **MUST** provide requirement level `[MUST|MUST NOT|SHOULD|SHOULD NOT|MAY]` for all items (see [IETF RFC 2119](https://datatracker.ietf.org/doc/html/rfc2119))
## Structure
* **MUST** `#include` minimal headers
	* use forward declarations where possible
	* provide forward declaration (`XxxFwd.h`) headers
	* provide template function definitions in separate implementation (`XxxImpl.h`) headers
	* `XxxFwd.h` <- `Xxx.h` <- `XxxImpl.h` <- `Xxx.cpp`
* **MUST** follow `#include` order for headers
	1. system/stl using `<>`
	1. external projects using `<>`
		* ensures `-I` for compiler is setup
	1. local to project (but not self) using `""`
	1. self using `""` is always last
	* Example
		* in `ThisClass.h`:
```
		#include <string>
		#include <boost/any.hpp>
		#include "AnotherClass.h"
		#include "ThisClassFwd.h"
```
* **MUST** follow `#include` order for non-headers (`*.cpp`)
	1. self using `""` is always first
		* ensures that project headers are self contained
	1. system/stl using `<>`
	1. external projects using `<>`
		* ensure `-I` for compiler is setup
	1. local to project (but not self) using `""`
	* Example
		* in `ThisClass.cpp`:
```
		#include "ThisClassImpl.h"
		#include <string>
		#include <boost/any.hpp>
		#include "AnotherClassImpl.h"
```
* **MUST NOT** include any non "Fwd" header in a "XxxFwd" header
* **SHOULD** Split header code logically into separate granular headers, typically by class and/or namespace
* **SHOULD** Consolidate non-header code into fewer compile units of manageable size, typically by namespace
* **SHOULD** beautify source consistently

## Naming
* **MUST** use `#define` that follows path + filename
	* `mylib/aaa/bbb/CccFwd.h` -> `#define MYLIB_AAA_BBB_CCCFWD_H`
	* ensures that classes with same name, but different namespace do not clash
* **SHOULD** use these naming conventions
	* single word lower case for namespace
	* CamelCase for class names and methods
	* Prefix of `_` for items that are meant to be hidden or not accessed directly
	* Suffix of `T` for template types
	* Suffix of `P` for pointer types
	* Prefix of `a` for arguments
	* Prefix of `m` for private member variables
	* CamelCase for public member variables (`struct`)
	* Secondary prefix of `r` for references
	* Prefix of `Is` for booleans 
		* do not try and use proper english conjugations of (to) Be 
* **SHOULD** use namespace to group code logically
* **SHOULD** have namespace name follow directory structure
	* `aaa::bbb::Ccc` code is in `aaa/bbb/` project subdirectory
* **SHOULD** use all capital namespace to wrap `enum`
	* **SHOULD NOT** use prefix of enum type in caps to prevent clash.  `COLOR_RED` :(
	* Exmaple
```
namespace COLOR
{
	enum Color
	{
		RED,
		BLUE
	};
}

auto color = COLOR::RED;
```
* **SHOULD** use inverse word order for compound names (embrace Yoda) to ensure alphabetical grouping of logically related things
	* Example: `ErrorRuntime()` & `ErrorRange()` not `RuntimeError()` & `RangeError()`
* **SHOULD** use namespaces rather than compound names with same prefix 
	* Example: `Error::Runtime()` & `Error::Range()` not `ErrorRuntime()` & `ErrorRange()`

## Inheritance
* **SHOULD** have public non-virtual wrapper to (protected) virtual methods
* **MUST** have common lifecycle methods
* **SHOULD** use default/delete rather than implement or hide
* **SHOULD** Relegate non-base classes to implementaton headers (XxxImpl.h)

## Misc
* **MUST** document the code within "Xxx.h" files
	* **MAY** document logic in "XxxImpl.h" and "Xxx.cpp" files within methods/functions
	* **SHOULD NOT** document elsewhere or replicate same docs between definition and declaration
* **SHOUL** use doxygen (javadoc) style documentation ('/// \<tag>')
* **SHOULD NOT** "inline", move code out of declarations and rely on definition locality
* **SHOULD** use `const` aggressively
* **SHOULD** use struct of arguments  instead of many individual arguments
* **SHOULD NOT** return a value and also have non-const reference argument
* **SHOULD** use `explicit` on any constructors with arguments
* **SHOULD NOT** return references
* 
## C++ 14/17/etc
* **SHOULD** use `auto`
* **SHOULD** return non-const type
* **SHOULD** use compound namespace rather than nest

## Templates
* **SHOULD** discourage code bloat
	* hoist
	* hide definitions and pre-instantiate
