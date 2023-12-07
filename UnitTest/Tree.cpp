#include "pch.h"
#include "CppUnitTest.h"

#include "../Serial/serial.h"

#include "Data.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace serial::tree
{
	class TestValueT : public Value
	{
	public:
		TestValueT(NODE::Node aNode, DATA::Data aData)
			: Value(aNode, aData)
		{
		}

		virtual void _Get(const serial::format::In& aF, std::istream& arIn)
		{
		}

		virtual void _Put(const serial::format::Out& aF, std::ostream& arOut) const
		{
		}
	};
}

namespace Tree
{
	TEST_CLASS(TestValue)
	{
	public:

		TEST_METHOD(Ctor)
		{
			using namespace serial::tree;

			if (true)
			{
				auto v = TestValueT(NODE::UNKNOWN, DATA::UNKNOWN);

				Assert::IsFalse(IsChildless(v));
				Assert::IsFalse(IsParent(v));

				Assert::IsFalse(IsNative(v));
				Assert::IsFalse(IsRange(v));
				Assert::IsFalse(IsPair(v));
				Assert::IsFalse(IsDict(v));
				Assert::IsFalse(IsUser(v));
			}
		}

		TEST_METHOD(Is)
		{
			using namespace serial::tree;

			if (true)
			{
				auto v = TestValueT(NODE::CHILDLESS, DATA::UNKNOWN);

				Assert::IsTrue(IsChildless(v));
				Assert::IsFalse(IsParent(v));
			}

			if (true)
			{
				auto v = TestValueT(NODE::PARENT, DATA::UNKNOWN);

				Assert::IsFalse(IsChildless(v));
				Assert::IsTrue(IsParent(v));
			}

			if (true)
			{
				auto v = TestValueT(NODE::UNKNOWN, DATA::NATIVE);

				Assert::IsTrue(IsNative(v));
				Assert::IsFalse(IsRange(v));
				Assert::IsFalse(IsPair(v));
				Assert::IsFalse(IsDict(v));
				Assert::IsFalse(IsUser(v));
			}

			if (true)
			{
				auto v = TestValueT(NODE::UNKNOWN, DATA::ARRAY);

				Assert::IsFalse(IsNative(v));
				Assert::IsTrue(IsRange(v));
				Assert::IsFalse(IsPair(v));
				Assert::IsFalse(IsDict(v));
				Assert::IsFalse(IsUser(v));
			}

			if (true)
			{
				auto v = TestValueT(NODE::UNKNOWN, DATA::PAIR);

				Assert::IsFalse(IsNative(v));
				Assert::IsFalse(IsRange(v));
				Assert::IsTrue(IsPair(v));
				Assert::IsFalse(IsDict(v));
				Assert::IsFalse(IsUser(v));
			}

			if (true)
			{
				auto v = TestValueT(NODE::UNKNOWN, DATA::DICT);

				Assert::IsFalse(IsNative(v));
				Assert::IsFalse(IsRange(v));
				Assert::IsFalse(IsPair(v));
				Assert::IsTrue(IsDict(v));
				Assert::IsFalse(IsUser(v));
			}

			if (true)
			{
				auto v = TestValueT(NODE::UNKNOWN, DATA::USER);

				Assert::IsFalse(IsNative(v));
				Assert::IsFalse(IsRange(v));
				Assert::IsFalse(IsPair(v));
				Assert::IsFalse(IsDict(v));
				Assert::IsTrue(IsUser(v));
			}
		}

		TEST_METHOD(Native)
		{
			using namespace serial::tree;

			auto d = int();
			auto p = serial::tree::Value::NativeP(d);

			Assert::IsFalse(IsParent(*p));
			Assert::IsTrue(IsChildless(*p));

			Assert::IsFalse(IsUser(*p));
			Assert::IsTrue(IsNative(*p));
			Assert::IsFalse(IsRange(*p));
			Assert::IsFalse(IsDict(*p));
			Assert::IsFalse(IsPair(*p));
		}

		TEST_METHOD(NativeGet)
		{
			using namespace serial::tree;

			auto readerP = serial::format::In::ReaderP(serial::format::TYPE::VALUE);

			if (true)
			{
				int d = 0;
				auto v = NativeT(d);

				Assert::AreEqual(0, d);

				v.Get(*readerP, std::istringstream("1"));

				Assert::AreEqual(1, d);
			}

			if (true)
			{
				auto d = false;
				auto v = NativeT(d);

				Assert::IsFalse(d);

				v.Get(*readerP, std::istringstream("1"));

				Assert::IsTrue(d);

				v.Get(*readerP, std::istringstream("0"));

				Assert::IsFalse(d);
			}

			if (true)
			{
				auto d = std::string("");
				auto v = NativeT(d);

				Assert::AreEqual(std::string(), d);

				v.Get(*readerP, std::istringstream("abc"));

				Assert::AreEqual(std::string("abc"), d);
			}
		}

		TEST_METHOD(NativePut)
		{
			using namespace serial::tree;
			using namespace serial::format;

			auto writerP = Out::WriterP(TYPE::VALUE);

			if (true)
			{
				int d = 0;
				auto n = NativeT(d);

				auto s = std::ostringstream("");
				n.Put(*writerP, s);
				Assert::AreEqual(std::string("0"), s.str());
			}

			if (true)
			{
				auto d = false;
				auto n = NativeT(d);

				auto s = std::ostringstream("");
				n.Put(*writerP, s);
				Assert::AreEqual(std::string("0"), s.str());
			}

			if (true)
			{
				auto d = std::string("abc");
				auto n = NativeT(d);

				auto s = std::ostringstream("");
				n.Put(*writerP, s);
				Assert::AreEqual(std::string("abc"), s.str());
			}
		}

		TEST_METHOD(User)
		{
			using namespace serial::tree;

			auto d = data::Value::UserNative();
			auto u = UserT(d);

			Assert::IsTrue(IsParent(u));
			Assert::IsFalse(IsChildless(u));

			Assert::IsTrue(IsUser(u));
			Assert::IsFalse(IsNative(u));
			Assert::IsFalse(IsRange(u));
			Assert::IsFalse(IsDict(u));
			Assert::IsFalse(IsPair(u));
		}

		TEST_METHOD(UserPut)
		{
			using namespace serial::tree;
			using namespace serial::format;

			auto writerP = Out::WriterP(TYPE::VALUE);

			if (true)
			{
				auto d = data::Value::UserNative();
				auto u = UserT(d);
				d.mI = 10;
				d.mB = true;
				d.mS = "abc";

				auto s = std::ostringstream("");
				u.Put(*writerP, s);
				Assert::AreEqual(std::string("10 1 abc"), s.str());
			}

			if (true)
			{
				auto d = data::Value::UserUser();
				auto u = UserT(d);
				d.mU.mI = 10;
				d.mU.mB = true;
				d.mU.mS = "abc";

				auto s = std::ostringstream("");
				u.Put(*writerP, s);
				Assert::AreEqual(std::string("10 1 abc"), s.str());
			}
		}

		TEST_METHOD(UserGet)
		{
			using namespace serial::tree;
			using namespace serial::format;

			auto readerP = In::ReaderP(TYPE::VALUE);

			if (true)
			{
				auto d = data::Value::UserNative();
				auto u = UserT(d);

				Assert::AreEqual(0, d.mI);
				Assert::IsFalse(d.mB);
				Assert::AreEqual(std::string(""), d.mS);

				u.Get(*readerP, std::istringstream("10 1 abc"));

				Assert::AreEqual(10, d.mI);
				Assert::IsTrue(d.mB);
				Assert::AreEqual(std::string("abc"), d.mS);
			}

			if (true)
			{
				auto d = data::Value::UserUser();
				auto u = UserT(d);

				Assert::AreEqual(0, d.mU.mI);
				Assert::IsFalse(d.mU.mB);
				Assert::AreEqual(std::string(""), d.mU.mS);

				u.Get(*readerP, std::istringstream("10 1 abc"));

				Assert::AreEqual(10, d.mU.mI);
				Assert::IsTrue(d.mU.mB);
				Assert::AreEqual(std::string("abc"), d.mU.mS);
			}
		}

		TEST_METHOD(Array)
		{
			using namespace serial::tree;

			auto d = std::vector<int>{ 1, 2, 3 };
			auto u = ArrayT(d);

			Assert::IsTrue(IsParent(u));
			Assert::IsFalse(IsChildless(u));

			Assert::IsFalse(IsUser(u));
			Assert::IsFalse(IsNative(u));
			Assert::IsTrue(IsRange(u));
			Assert::IsFalse(IsDict(u));
			Assert::IsFalse(IsPair(u));
		}

		TEST_METHOD(ArrayPut)
		{
			using namespace serial::tree;
			using namespace serial::format;

			auto writerP = Out::WriterP(TYPE::VALUE);

			if (true)
			{
				auto d = std::vector<int>{ 1, 2, 3 };
				auto u = ArrayT(d);

				auto s = std::ostringstream("");
				u.Put(*writerP, s);
				Assert::AreEqual(std::string("3 1 2 3"), s.str());
			}

			if (true)
			{
				auto d = data::Value::UserVector();
				auto u = UserT(d);

				auto s = std::ostringstream("");
				u.Put(*writerP, s);
				Assert::AreEqual(std::string("3 1 2 3"), s.str());
			}

			if (true)
			{
				auto d = data::Value::UserVectorVector();
				auto u = UserT(d);

				auto s = std::ostringstream("");
				u.Put(*writerP, s);
				Assert::AreEqual(std::string("1 3 1 2 3"), s.str());
			}
		}

		TEST_METHOD(ArrayGet)
		{
			using namespace serial::tree;
			using namespace serial::format;

			auto readerP = In::ReaderP(TYPE::VALUE);

			if (true)
			{
				auto d = std::vector<int>{};
				auto u = ArrayT(d);

				Assert::AreEqual(0ULL, d.size());

				u.Get(*readerP, std::istringstream("2 1 0"));

				Assert::AreEqual(2ULL, d.size());
				Assert::AreEqual(1, d[0]);
				Assert::AreEqual(0, d[1]);
			}

			if (true)
			{
				auto d = data::Value::UserVector();
				auto u = UserT(d);

				Assert::AreEqual(3ULL, d.mIs.size());

				u.Get(*readerP, std::istringstream("2 1 0"));

				Assert::AreEqual(2ULL, d.mIs.size());
				Assert::AreEqual(1, d.mIs[0]);
				Assert::AreEqual(0, d.mIs[1]);
			}

			if (true)
			{
				auto d = data::Value::UserVectorVector();
				auto u = UserT(d);

				Assert::AreEqual(1ULL, d.mIIs.size());
				Assert::AreEqual(3ULL, d.mIIs[0].size());

				u.Get(*readerP, std::istringstream("2 1 2 2 1 0"));

				Assert::AreEqual(2ULL, d.mIIs.size());
				Assert::AreEqual(1ULL, d.mIIs[0].size());
				Assert::AreEqual(2ULL, d.mIIs[1].size());
				Assert::AreEqual(2, d.mIIs[0][0]);
				Assert::AreEqual(1, d.mIIs[1][0]);
				Assert::AreEqual(0, d.mIIs[1][1]);
			}

		}

		TEST_METHOD(Pair)
		{
			using namespace serial::tree;

			auto d = std::pair<int, int>(1, 2);
			auto u = PairT(d);

			Assert::IsTrue(IsParent(u));
			Assert::IsFalse(IsChildless(u));

			Assert::IsFalse(IsUser(u));
			Assert::IsFalse(IsNative(u));
			Assert::IsFalse(IsRange(u));
			Assert::IsFalse(IsDict(u));
			Assert::IsTrue(IsPair(u));
		}

		TEST_METHOD(PairPut)
		{
			using namespace serial::tree;
			using namespace serial::format;

			auto writerP = Out::WriterP(TYPE::VALUE);

			if (true)
			{
				auto d = std::pair<int, int>(1, 2);
				auto u = PairT(d);

				auto s = std::ostringstream("");
				u.Put(*writerP, s);
				Assert::AreEqual(std::string("1 2"), s.str());
			}

			if (true)
			{
				auto d = data::Value::UserPair();
				auto u = UserT(d);

				auto s = std::ostringstream("");
				u.Put(*writerP, s);
				Assert::AreEqual(std::string("1 abc"), s.str());
			}

			if (true)
			{
				auto d = data::Value::UserPairPair();
				auto u = UserT(d);

				auto s = std::ostringstream("");
				u.Put(*writerP, s);
				Assert::AreEqual(std::string("1 abc 1"), s.str());
			}
		}

		TEST_METHOD(PairGet)
		{
			using namespace serial::tree;
			using namespace serial::format;

			auto readerP = In::ReaderP(TYPE::VALUE);

			if (true)
			{
				auto d = std::pair<int, int>(1, 2);
				auto u = PairT(d);

				Assert::AreEqual(1, d.first);
				Assert::AreEqual(2, d.second);

				u.Get(*readerP, std::istringstream("3 4"));

				Assert::AreEqual(3, d.first);
				Assert::AreEqual(4, d.second);
			}

			if (true)
			{
				auto d = data::Value::UserPair();
				auto u = UserT(d);

				Assert::AreEqual(1, d.mP.first);
				Assert::AreEqual(std::string("abc"), d.mP.second);

				u.Get(*readerP, std::istringstream("2 xyz"));

				Assert::AreEqual(2, d.mP.first);
				Assert::AreEqual(std::string("xyz"), d.mP.second);
			}

			if (true)
			{
				auto d = data::Value::UserPairPair();
				auto u = UserT(d);

				Assert::AreEqual(1, d.mPP.first);
				Assert::AreEqual(std::string("abc"), d.mPP.second.first);
				Assert::AreEqual(true, d.mPP.second.second);

				u.Get(*readerP, std::istringstream("2 xyz 0"));

				Assert::AreEqual(2, d.mPP.first);
				Assert::AreEqual(std::string("xyz"), d.mPP.second.first);
				Assert::AreEqual(false, d.mPP.second.second);
			}
		}

		TEST_METHOD(Dict)
		{
			using namespace serial::tree;

			if (true)
			{
				auto d = std::map<int, int>{ {1, 2} };
				auto u = DictT(d);

				Assert::IsTrue(IsParent(u));
				Assert::IsFalse(IsChildless(u));

				Assert::IsFalse(IsUser(u));
				Assert::IsFalse(IsNative(u));
				Assert::IsFalse(IsRange(u));
				Assert::IsTrue(IsDict(u));
				Assert::IsFalse(IsPair(u));
			}

			if (true)
			{
				auto d = std::set<int>{ 1, 2 };
				auto u = DictT(d);

				Assert::IsTrue(IsParent(u));
				Assert::IsFalse(IsChildless(u));

				Assert::IsFalse(IsUser(u));
				Assert::IsFalse(IsNative(u));
				Assert::IsFalse(IsRange(u));
				Assert::IsTrue(IsDict(u));
				Assert::IsFalse(IsPair(u));
			}
		}

		TEST_METHOD(DictPut)
		{
			using namespace serial::tree;
			using namespace serial::format;

			auto writerP = Out::WriterP(TYPE::VALUE);

			if (true)
			{
				auto d = std::set<int>{ 1, 2, 3 };
				auto u = DictT(d);

				auto s = std::ostringstream("");
				u.Put(*writerP, s);

				Assert::AreEqual(std::string("3 1 2 3"), s.str());
			}

			if (true)
			{
				auto d = data::Value::UserSet();
				auto u = UserT(d);

				auto s = std::ostringstream("");
				u.Put(*writerP, s);
				Assert::AreEqual(std::string("3 1 2 3"), s.str());
			}

			if (true)
			{
				auto d = std::map<int, int>{ {1, 2} };
				auto u = DictT(d);

				auto s = std::ostringstream("");
				u.Put(*writerP, s);

				Assert::AreEqual(std::string("1 1 2"), s.str());
			}

			if (true)
			{
				auto d = data::Value::UserDict();
				auto u = UserT(d);

				auto s = std::ostringstream("");
				u.Put(*writerP, s);
				Assert::AreEqual(std::string("1 1 abc"), s.str());
			}

			if (true)
			{
				auto d = data::Value::UserDictDict();
				auto u = UserT(d);

				auto s = std::ostringstream("");
				u.Put(*writerP, s);
				Assert::AreEqual(std::string("1 1 1 abc 1"), s.str());
			}
		}

		TEST_METHOD(DictGet)
		{
			using namespace serial::tree;
			using namespace serial::format;

			auto readerP = In::ReaderP(TYPE::VALUE);

			if (true)
			{
				auto d = std::set<int>{ 1, 2, 3 };
				auto u = DictT(d);

				Assert::AreEqual(3ULL, d.size());
				Assert::AreEqual(1ULL, d.count(1));
				Assert::AreEqual(1ULL, d.count(2));
				Assert::AreEqual(1ULL, d.count(3));

				u.Get(*readerP, std::istringstream("2 3 4"));

				Assert::AreEqual(2ULL, d.size());
				Assert::AreEqual(1ULL, d.count(3));
				Assert::AreEqual(1ULL, d.count(4));
			}

			if (true)
			{
				auto d = data::Value::UserSet();
				auto u = UserT(d);

				Assert::AreEqual(3ULL, d.mS.size());
				Assert::AreEqual(1ULL, d.mS.count(1));
				Assert::AreEqual(1ULL, d.mS.count(2));
				Assert::AreEqual(1ULL, d.mS.count(3));

				u.Get(*readerP, std::istringstream("2 3 4"));

				Assert::AreEqual(2ULL, d.mS.size());
				Assert::AreEqual(1ULL, d.mS.count(3));
				Assert::AreEqual(1ULL, d.mS.count(4));
			}

			if (true)
			{
				auto d = std::map<int, int>{ {1, 2} };
				auto u = DictT(d);

				Assert::AreEqual(1ULL, d.size());
				Assert::AreEqual(2, d[1]);

				u.Get(*readerP, std::istringstream("2 3 4 5 6"));

				Assert::AreEqual(2ULL, d.size());
				Assert::AreEqual(4, d[3]);
				Assert::AreEqual(6, d[5]);
			}

			if (true)
			{
				auto d = data::Value::UserDict();
				auto u = UserT(d);

				Assert::AreEqual(1ULL, d.mD.size());
				Assert::AreEqual(std::string("abc"), d.mD[1]);

				u.Get(*readerP, std::istringstream("2 2 qwe 3 xyz"));

				Assert::AreEqual(2ULL, d.mD.size());
				Assert::AreEqual(std::string("qwe"), d.mD[2]);
				Assert::AreEqual(std::string("xyz"), d.mD[3]);
			}

			if (true)
			{
				auto d = data::Value::UserDictDict();
				auto u = UserT(d);

				Assert::AreEqual(1ULL, d.mDD.size());
				Assert::AreEqual(1ULL, d.mDD[1].size());
				Assert::AreEqual(true, d.mDD[1]["abc"]);

				u.Get(*readerP, std::istringstream("1 3 2 qwe 1 xyz 0"));

				Assert::AreEqual(1ULL, d.mDD.size());
				Assert::AreEqual(2ULL, d.mDD[3].size());
				Assert::AreEqual(true, d.mDD[3]["qwe"]);
				Assert::AreEqual(false, d.mDD[3]["xyz"]);
			}

		}


	};
}


std::string Name(const serial::format::Out& aF, const serial::tree::Key& aKey)
{
	std::ostringstream data("");
	aKey.Put(aF, data);

	return data.str();
}

namespace Tree
{
	TEST_CLASS(TestKey)
	{
	public:

		TEST_METHOD(Ctor)
		{
			auto k = serial::tree::Key("test");

			Assert::AreEqual(std::string("test"), k.mId);
			Assert::IsTrue(k.mIsValid);

			auto writerP = serial::format::Out::WriterP(serial::format::TYPE::VALUE);

			Assert::AreEqual(std::string("test"), Name(*writerP, k));
		}

		TEST_METHOD(Static)
		{
			using serial::tree::Key;

			auto writerP = serial::format::Out::WriterP(serial::format::TYPE::VALUE);

			Assert::AreEqual(std::string("dict"), Name(*writerP, Key::Dict()));
			Assert::AreEqual(std::string("items"), Name(*writerP, Key::Items()));
			Assert::AreEqual(std::string("len"), Name(*writerP, Key::Len()));
			Assert::AreEqual(std::string("user"), Name(*writerP, Key::User()));
		}

		TEST_METHOD(Copy)
		{
			using serial::tree::Key;

			auto k = serial::tree::Key("test");
			auto c(k);

			Assert::AreEqual(std::string("test"), c.mId);
			Assert::IsTrue(c.mIsValid);

			auto writerP = serial::format::Out::WriterP(serial::format::TYPE::VALUE);

			Assert::AreEqual(std::string("test"), Name(*writerP, c));
		}

		TEST_METHOD(EqualOp)
		{
			using serial::tree::Key;

			auto k = serial::tree::Key("test");
			auto c = k;

			Assert::AreEqual(std::string("test"), c.mId);
			Assert::IsTrue(c.mIsValid);

			auto writerP = serial::format::Out::WriterP(serial::format::TYPE::VALUE);

			Assert::AreEqual(std::string("test"), Name(*writerP, c));
		}


	};
}


namespace Tree
{
	TEST_CLASS(TestElem)
	{
	public:

		TEST_METHOD(Ctor)
		{
			using namespace serial::tree;

			auto u = data::Member();
			auto e = Elem(Key::User(), Value::UserP(u));

			Assert::AreEqual(std::string("user"), e.mKey.mId);
			Assert::IsTrue(e.mKey.mIsValid);

			Assert::IsTrue(IsParent(*(e.mValueP)));
			Assert::IsTrue(IsUser(*(e.mValueP)));
		}

	};
}


namespace Tree
{
	TEST_CLASS(TestNode)
	{
	public:

		TEST_METHOD(Member)
		{
			using namespace serial;

			auto d = data::Member();
			Assert::AreEqual(0, d.M());

			std::stringstream s("3");
			auto readerP = format::In::ReaderP(format::TYPE::VALUE);

			auto e = tree::Node(d);
			readerP->Read(s, e);

			Assert::AreEqual(3, d.M());
		}

		TEST_METHOD(Inherit)
		{
			using namespace serial;

			auto d = data::Inherit();
			Assert::AreEqual(0, d.M());

			std::stringstream s("4");
			auto readerP = format::In::ReaderP(format::TYPE::VALUE);

			auto e = tree::Node(d);
			readerP->Read(s, e);

			Assert::AreEqual(4, d.M());
		}

		TEST_METHOD(Free)
		{
			using namespace serial;

			auto d = data::Free();
			Assert::AreEqual(0, d.m);

			std::stringstream s("5");
			auto readerP = format::In::ReaderP(format::TYPE::VALUE);

			auto e = tree::Node(d);
			readerP->Read(s, e);

			Assert::AreEqual(5, d.m);
		}

	};
}

