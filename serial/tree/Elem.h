#ifndef SERIAL_TREE_ELEM_H
#define SERIAL_TREE_ELEM_H

#include <string>

#include "Key.h"
#include "ValueFwd.h"

#include "ElemFwd.h"

namespace serial::tree
{
	class Elem
	{
	public:
		Key mKey;

		ValueP mValueP;

	public:
		Elem();

		Elem(const Elem& aElem);

		Elem& operator=(const Elem& aElem) = delete;

		Elem(const Key& aKey, const ValueP& aValue);

		virtual ~Elem() = default;

		bool IsParent() const;
		bool IsChildless() const;

		bool IsUser() const;
		bool IsNative() const;
		bool IsRange() const;
		bool IsDict() const;
		bool IsPair() const;

		const std::string TypeDataName() const;

		const std::string TypeNodeName() const;

	};

}

#endif

