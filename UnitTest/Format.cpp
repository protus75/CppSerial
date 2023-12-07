#include "pch.h"
#include "CppUnitTest.h"

#include "../Serial/format/FormatImpl.h"
#include "../Serial/tree/NodeImpl.h"

#include "Data.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace Format
{
	TEST_CLASS(IO)
	{
	public:

		TEST_METHOD(In)
		{
			using namespace serial::tree;
			using namespace serial::format;

			if (true)
			{
				auto readerP = In::ReaderP(TYPE::KEY_EQ_VALUE);

				auto d = data::Value::UserUser();
				auto u = UserT(d);

				Assert::AreEqual(0, d.mU.mI);
				Assert::IsFalse(d.mU.mB);
				Assert::AreEqual(std::string(""), d.mU.mS);

				u.Get(*readerP, std::istringstream("int=10 bool=1 string=abc"));

				Assert::AreEqual(10, d.mU.mI);
				Assert::IsTrue(d.mU.mB);
				Assert::AreEqual(std::string("abc"), d.mU.mS);
			}
		}

		TEST_METHOD(Out)
		{
			using namespace serial::tree;
			using namespace serial::format;

			if (true)
			{
				auto writerP = Out::WriterP(TYPE::KEY_EQ_VALUE);

				auto d = data::Value::UserUser();
				auto u = UserT(d);
				d.mU.mI = 10;
				d.mU.mB = true;
				d.mU.mS = "abc";

				auto s = std::ostringstream("");
				u.Put(*writerP, s);
				Assert::AreEqual(std::string("int=10 bool=1 string=abc"), s.str());
			}

		}
	};
}



