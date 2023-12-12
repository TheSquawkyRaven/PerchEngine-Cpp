#include "pch.h"

#include "../PerchEngine-Cpp/src/Structs/Vector2.h"

using namespace Perch;

template<typename T>
bool EQ(const T& lhs, const const T& rhs)
{
	return (T)lhs == rhs;
}

class Vector2Test : public testing::Test
{

public:

	static bool EQ(Vector2 lhs, Vector2 rhs)
	{
		return lhs == rhs;
	}

protected:
	void SetUp() override
	{
		Vector2(5, 2) == Vector2(2, 5);
	}

};

TEST(TestCaseName, TestName)
{
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
}

TEST(Vector2Test, Equality)
{
	ASSERT_TRUE(EQ(Vector2(), Vector2()));
	ASSERT_TRUE(EQ(Vector2::Zero(), Vector2(0.f, 0.f)));
	ASSERT_TRUE(EQ(Vector2::Zero(), Vector2()));
	ASSERT_TRUE(EQ(Vector2::One(), Vector2(1, 1)));
	ASSERT_TRUE(EQ(Vector2::Half(), Vector2(0.5f, 0.5f)));

	ASSERT_TRUE(EQ(Vector2(4, 2), Vector2(4.f, 2.f)));
	ASSERT_TRUE(EQ(Vector2(7.2f, 999.4f), Vector2(7.2f, 999.4f)));
	ASSERT_TRUE(EQ(Vector2(-64.5f, 5.f), Vector2(-64.5f, 5)));
	ASSERT_FALSE(EQ(Vector2(-2.5f, 5.f), Vector2(-2, 5.f)));
	ASSERT_FALSE(EQ(Vector2(-2.f, 3.f), Vector2(2, 3.f)));

	ASSERT_TRUE(EQ(Vector2::Left(), Vector2(0.f, 0.5f)));
	ASSERT_TRUE(EQ(Vector2::Right(), Vector2(1.f, 0.5f)));
	ASSERT_TRUE(EQ(Vector2::Down(), Vector2(0.5f, 1.f)));
	ASSERT_TRUE(EQ(Vector2::Up(), Vector2(0.5f, 0.f)));

	ASSERT_TRUE(EQ(Vector2::TopLeft(), Vector2(0.f, 0.f)));
	ASSERT_TRUE(EQ(Vector2::TopRight(), Vector2(1.f, 0.f)));
	ASSERT_TRUE(EQ(Vector2::BottomLeft(), Vector2(0.f, 1.f)));
	ASSERT_TRUE(EQ(Vector2::BottomRight(), Vector2(1.f, 1.f)));
	
}
