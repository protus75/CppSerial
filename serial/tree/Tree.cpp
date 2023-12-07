#include "../memory/SingletonImpl.h"

#include "ValueImpl.h"
#include "KeyImpl.h"
#include "ElemImpl.h"
#include "PeersImpl.h"
#include "NodeImpl.h"

namespace serial::tree
{
	Key::Key()
		: NativeT<std::string>(mId)
		, mIsValid(false)
		, mId()
	{}

	Key::Key(const std::string& aId)
		: NativeT<std::string>(mId)
		, mIsValid(true)
		, mId(aId)
	{}

	Key::~Key()
	{}

	Key::Key(const Key& aKey)
		: NativeT<std::string>(mId)
		, mIsValid(true)
		, mId(aKey.mId)
	{}

	Key& Key::operator=(const Key& aKey)
	{
		if (this != &aKey)
		{
			mIsValid = aKey.mIsValid;
			mId = aKey.mId;
		}

		return *this;
	}
}

namespace serial::tree
{
	using serial::memory::Instance;

	struct Keys
	{
		Key User = Key("user");
		Key Array = Key("array");
		Key Dict = Key("dict");
		Key Len = Key("len");
		Key Pair = Key("pair");
		Key Items = Key("items");
		Key Int = Key("int");
		Key String = Key("string");
		Key Bool = Key("bool");
	};

	const Key& Key::User()
	{
		return Instance<Keys>().User;
	}

	const Key& Key::Array()
	{
		return Instance<Keys>().Array;
	}

	const Key& Key::Dict()
	{
		return Instance<Keys>().Dict;
	}

	const Key& Key::Len()
	{
		return Instance<Keys>().Len;
	}

	const Key& Key::Pair()
	{
		return Instance<Keys>().Pair;
	}

	const Key& Key::Items()
	{
		return Instance<Keys>().Items;
	}

	template <>
	const Key& Key::Native<int>()
	{
		return Instance<Keys>().Int;
	}

	template <>
	const Key& Key::Native<bool>()
	{
		return Instance<Keys>().Bool;
	}

	template <>
	const Key& Key::Native<std::string>()
	{
		return Instance<Keys>().String;
	}

}


namespace serial::tree
{
	namespace DATA
	{
		const std::string Name(Data aType)
		{
			switch (aType)
			{
			case NATIVE: return "native";
			case ARRAY: return "array";
			case PAIR: return "pair";
			case DICT: return "dict";
			case USER: return "user";

			default: return "unmapped_type";
			}

			return "error";
		}
	}

	namespace NODE
	{
		const std::string Name(Node aType)
		{
			switch (aType)
			{
			case PARENT: return "parent";
			case CHILDLESS: return "childless";

			default: return "unmapped_type";
			}

			return "error";
		}
	}

	Value::Value(NODE::Node aNode, DATA::Data aData)
		: mTypeData(aData)
		, mTypeNode(aNode)
	{
	}

	void Value::Get(const serial::format::In& aF, std::istream& arIn)
	{
		_Get(aF, arIn);
	}

	void Value::Put(const serial::format::Out& aF, std::ostream& arOut) const
	{
		_Put(aF, arOut);
	}


	bool IsUser(DATA::Data aType)
	{
		return aType == DATA::USER;
	}

	bool IsNative(DATA::Data aType)
	{
		return aType == DATA::NATIVE;
	}

	bool IsRange(DATA::Data aType)
	{
		return aType == DATA::ARRAY;
	}

	bool IsDict(DATA::Data aType)
	{
		return aType == DATA::DICT;
	}

	bool IsPair(DATA::Data aType)
	{
		return aType == DATA::PAIR;
	}


	bool IsParent(NODE::Node aType)
	{
		return aType == NODE::PARENT;
	}

	bool IsChildless(NODE::Node aType)
	{
		return aType == NODE::CHILDLESS;
	}
}


namespace serial::tree
{
	bool IsUser(const Value& aValue)
	{
		return IsUser(aValue.mTypeData);
	}

	bool IsNative(const Value& aValue)
	{
		return IsNative(aValue.mTypeData);
	}

	bool IsRange(const Value& aValue)
	{
		return IsRange(aValue.mTypeData);
	}

	bool IsDict(const Value& aValue)
	{
		return IsDict(aValue.mTypeData);
	}

	bool IsPair(const Value& aValue)
	{
		return IsPair(aValue.mTypeData);
	}


	bool IsParent(const Value& aValue)
	{
		return IsParent(aValue.mTypeNode);
	}

	bool IsChildless(const Value& aValue)
	{
		return IsChildless(aValue.mTypeNode);
	}


	const std::string TypeDataName(const Value& aValue)
	{
		return DATA::Name(aValue.mTypeData);
	}


	const std::string TypeNodeName(const Value& aValue)
	{
		return NODE::Name(aValue.mTypeNode);
	}
}

namespace serial::tree
{
	static auto gKey = Key();
	Elem::Elem()
		: mKey(gKey)
		, mValueP(NULL)
	{
	}

	Elem::Elem(const Elem& aElem)
		: mKey(aElem.mKey)
		, mValueP(aElem.mValueP)
	{
	}

	Elem::Elem(const Key& aKey, const ValueP& aValueP)
		: mKey(aKey)
		, mValueP(aValueP)
	{}

	bool Elem::IsParent() const
	{
		return tree::IsParent(*mValueP);
	}

	bool Elem::IsChildless() const
	{
		return tree::IsChildless(*mValueP);
	}

	bool Elem::IsUser() const
	{
		return tree::IsUser(*mValueP);
	}

	bool Elem::IsNative() const
	{
		return tree::IsNative(*mValueP);
	}

	bool Elem::IsRange() const
	{
		return tree::IsRange(*mValueP);
	}

	bool Elem::IsDict() const
	{
		return tree::IsDict(*mValueP);
	}

	bool Elem::IsPair() const
	{
		return tree::IsPair(*mValueP);
	}

	const std::string Elem::TypeDataName() const
	{
		return tree::TypeDataName(*mValueP);
	}

	const std::string Elem::TypeNodeName() const
	{
		return tree::TypeNodeName(*mValueP);
	}


}

namespace serial::tree
{
	size_t Peers::Len() const
	{
		return mItems.size();
	}

}

namespace serial::tree
{
	void Connect::Children(Peers& arKids)
	{
		_Children(arKids);
	}
}

namespace serial::tree
{
	template <typename T>
	Elem _Elem(T& arSelf)
	{
		return Elem(Key::Native<T>(), Value::NativeP(arSelf));
	}

	template <typename T>
	Elem _Elem(T& arSelf, const std::string& aId)
	{
		return Elem(Key(aId), Value::NativeP(arSelf));
	}


	template <>
	Elem _Node<int>::Node(int& arSelf)
	{
		return _Elem(arSelf);
	}

	template <>
	Elem _Node<int>::Node(int& arSelf, const std::string& aId)
	{
		return _Elem(arSelf, aId);
	}

	template <>
	Elem _Node<bool>::Node(bool& arSelf)
	{
		return _Elem(arSelf);
	}

	template <>
	Elem _Node<bool>::Node(bool& arSelf, const std::string& aId)
	{
		return _Elem(arSelf, aId);
	}

	template <>
	Elem _Node<std::string>::Node(std::string& arSelf)
	{
		return _Elem(arSelf);
	}

	template <>
	Elem _Node<std::string>::Node(std::string& arSelf, const std::string& aId)
	{
		return _Elem(arSelf, aId);
	}
}
