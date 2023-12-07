#ifndef SERIAL_TREE_KEY_H
#define SERIAL_TREE_KEY_H

#include <string>

#include "Value.h"

#include "KeyFwd.h"

namespace serial::tree
{
	struct Key : public NativeT<std::string>
	{
		Key();

		explicit Key(const std::string& aId);

		virtual ~Key();

		Key(const Key& aKey);

		Key& operator=(const Key& aKey);

		bool mIsValid;

		std::string mId;


		template <typename T>
		static const Key& Native();

		static const Key& User();

		static const Key& Array();

		static const Key& Len();

		static const Key& Pair();

		static const Key& Dict();

		static const Key& Items();

	};

	template <>
	const Key& Key::Native<int>();

	/// \todo the other number types

	template <>
	const Key& Key::Native<std::string>();

	template <>
	const Key& Key::Native<bool>();

}
#endif