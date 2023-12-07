#ifndef SERIAL_TREE_VALUE_H
#define SERIAL_TREE_VALUE_H

#include <string>
#include <iosfwd>

#include "ValueFwd.h"
#include "../format/FormatFwd.h"

namespace serial::tree
{
	namespace DATA {
		enum Data {
			UNKNOWN,
			NATIVE,
			ARRAY,
			PAIR,
			DICT,
			USER
		};

		const std::string Name(Data aType);
	}

	namespace NODE {
			enum Node {
			UNKNOWN,
			PARENT,
			CHILDLESS
		};

		const std::string Name(Node aData);
	}


	class Value {
	public:
		NODE::Node mTypeNode;

		DATA::Data mTypeData;

	public:		
		template <typename T>
		static ValueP NativeP(T& arSelf);

		template <typename T>
		static ValueP ArrayP(T& arSelf);

		template <typename T>
		static ValueP PairP(T& arSelf);

		template <typename T>
		static ValueP DictP(T& arSelf);

		template <typename T>
		static ValueP UserP(T& arSelf);

	public:
		explicit Value(NODE::Node aNode, DATA::Data aData);

		void Get(const serial::format::In& aF, std::istream& arIn);

		void Put(const serial::format::Out& aF, std::ostream& arOut) const;

	protected:
		virtual void _Get(const serial::format::In& aF, std::istream& arIn) = 0;

		virtual void _Put(const serial::format::Out& aF, std::ostream& arOut) const = 0;
	};

	template <typename T> class ValueT : public Value
	{
	public:
		ValueT(NODE::Node aNode, DATA::Data aData, T& arSelf);

		T& mrT;

		ValueT() = delete;
	};

	template <typename T>
	class NativeT : public ValueT<T>
	{
	public:
		NativeT(T& arSelf);

		NativeT() = delete;

	protected:
		void _Get(const serial::format::In& aF, std::istream& arIn) final;

		void _Put(const serial::format::Out& aF, std::ostream& arOut) const final;

	};

	template <typename T>
	class UserT : public ValueT<T>
	{
	public:
		UserT(T& arSelf);

		UserT() = delete;

	protected:
		void _Get(const serial::format::In& aF, std::istream& arIn) final;

		void _Put(const serial::format::Out& aF, std::ostream& arOut) const final;

	};

	template <typename T>
	class ArrayT : public ValueT<T>
	{
	public:
		ArrayT(T& arSelf);

		ArrayT() = delete;

	protected:
		void _Get(const serial::format::In& aF, std::istream& arIn) final;

		void _Put(const serial::format::Out& aF, std::ostream& arOut) const final;

	};

	template <typename T, typename U>
	class PairT : public ValueT<std::pair<T, U>>
	{
	public:
		PairT(std::pair<T, U>& arSelf);

	private:
		void _Get(const serial::format::In& aF, std::istream& arIn) final;

		void _Put(const serial::format::Out& aF, std::ostream& arOut) const final;

		PairT() = delete;
	};

	template <typename T>
	class DictT : public ValueT<T>
	{
	public:
		DictT(T& arSelf);

		DictT() = delete;

	protected:
		void _Get(const serial::format::In& aF, std::istream& arIn) final;

		void _Put(const serial::format::Out& aF, std::ostream& arOut) const final;

	};

	bool IsNative(const Value& aValue);
	bool IsRange(const Value& aValue);
	bool IsPair(const Value& aValue);
	bool IsDict(const Value& aValue);
	bool IsUser(const Value& aValue);

	bool IsParent(const Value& aValue);
	bool IsChildless(const Value& aValue);

}

#endif
