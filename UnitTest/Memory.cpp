#include "pch.h"
#include "CppUnitTest.h"

#include "../Serial/memory/SingletonImpl.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


int gN(0);
int gId(0);

namespace Memory
{
	struct Single
	{
		Single()
			: mId(gId++)
			, mN(gN)
		{
		}

		int mId;
		int mN;
	};
}

namespace serial::memory
{
	template <> void SingletonImpl<Memory::Single>::InstancePost()
	{
		++gN;
	}

	template <> void SingletonImpl<Memory::Single>::DeletePre()
	{
		--gN;
	}
}

class Singleton {
public:
	void Instance() {}
};

namespace Memory
{
	TEST_CLASS(Singleton)
	{
	public:

		TEST_METHOD(Instance)
		{
			Assert::AreEqual(0, serial::memory::Instance<Single>().mId);

			Assert::IsTrue(serial::memory::IsExist<Single>());

			Assert::AreEqual(0, serial::memory::Instance<Single>().mId);

			serial::memory::Delete<Single>();
			Assert::IsFalse(serial::memory::IsExist<Single>());

			Assert::AreEqual(1, serial::memory::Instance<Single>().mId);
		}
	};
}
