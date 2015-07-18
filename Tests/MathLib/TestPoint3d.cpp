/**
 * @file TestPoint3d.cpp
 * @author Thomas Fischer
 * @date Nov 8, 2012
 *
 * @copyright
 * Copyright (c) 2012-2015, OpenGeoSys Community (http://www.opengeosys.org)
 *            Distributed under a Modified BSD License.
 *              See accompanying file LICENSE.txt or
 *              http://www.opengeosys.org/LICENSE.txt
 */

#include <ctime>
#include "gtest/gtest.h"
#include "autocheck/autocheck.hpp"

#include "MathLib/Point3d.h"

#include "AutoCheckTools.h"

using namespace MathLib;
namespace ac = autocheck;

struct MathLibPoint3d : public ::testing::Test
{
	ac::randomTupleGenerator<double, 3> tupleGen{};
	ac::cons_generator<MathLib::Point3d, ac::randomTupleGenerator<double, 3>>
		pointGenerator{tupleGen};

	ac::gtest_reporter gtest_reporter;
};

TEST(MathLib, Point3dComparisonLessEq)
{
	// first coordinate
	ASSERT_TRUE(lessEq(Point3d(std::array<double,3>({{0,1,1}})),Point3d(std::array<double,3>({{1,1,1}}))));
	ASSERT_FALSE(lessEq(Point3d(std::array<double,3>({{1,1,1}})),Point3d(std::array<double,3>({{0,1,1}}))));
	// second coordinate
	ASSERT_TRUE(lessEq(Point3d(std::array<double,3>({{1,0,1}})),Point3d(std::array<double,3>({{1,1,1}}))));
	ASSERT_FALSE(lessEq(Point3d(std::array<double,3>({{1,1,1}})),Point3d(std::array<double,3>({{1,0,1}}))));
	// third coordinate
	ASSERT_TRUE(lessEq(Point3d(std::array<double,3>({{1,1,0}})),Point3d(std::array<double,3>({{1,1,1}}))));
	ASSERT_FALSE(lessEq(Point3d(std::array<double,3>({{1,1,1}})),Point3d(std::array<double,3>({{1,1,0}}))));

	const double e(2*std::numeric_limits<double>::epsilon());
	// first coordinate
	ASSERT_TRUE(lessEq(Point3d(std::array<double,3>({{1-e,1,1}})),Point3d(std::array<double,3>({{1,1,1}}))));
	ASSERT_FALSE(lessEq(Point3d(std::array<double,3>({{1,1,1}})),Point3d(std::array<double,3>({{1-e,1,1}}))));
	// second coordinate
	ASSERT_TRUE(lessEq(Point3d(std::array<double,3>({{1,1-e,1}})),Point3d(std::array<double,3>({{1,1,1}}))));
	ASSERT_FALSE(lessEq(Point3d(std::array<double,3>({{1,1,1}})),Point3d(std::array<double,3>({{1,1-e,1}}))));
	// third coordinate
	ASSERT_TRUE(lessEq(Point3d(std::array<double,3>({{1,1,1-e}})),Point3d(std::array<double,3>({{1,1,1}}))));
	ASSERT_FALSE(lessEq(Point3d(std::array<double,3>({{1,1,1}})),Point3d(std::array<double,3>({{1,1,1-e}}))));

	ASSERT_TRUE(lessEq(Point3d(std::array<double,3>({{1,1,1}})),Point3d(std::array<double,3>({{1,1,1}}))));

	const double half_eps(0.5*std::numeric_limits<double>::epsilon());
	ASSERT_TRUE(lessEq(Point3d(std::array<double,3>({{1+half_eps,1,1}})),Point3d(std::array<double,3>({{1,1,1}}))));
	ASSERT_TRUE(lessEq(Point3d(std::array<double,3>({{1,1+half_eps,1}})),Point3d(std::array<double,3>({{1,1,1}}))));
	ASSERT_TRUE(lessEq(Point3d(std::array<double,3>({{1,1,1+half_eps}})),Point3d(std::array<double,3>({{1,1,1}}))));
	ASSERT_TRUE(lessEq(Point3d(std::array<double,3>({{1,1,1}})),Point3d(std::array<double,3>({{1+half_eps,1,1}}))));
	ASSERT_TRUE(lessEq(Point3d(std::array<double,3>({{1,1,1}})),Point3d(std::array<double,3>({{1,1+half_eps,1}}))));
	ASSERT_TRUE(lessEq(Point3d(std::array<double,3>({{1,1,1}})),Point3d(std::array<double,3>({{1,1,1+half_eps}}))));

	ASSERT_TRUE(lessEq(Point3d(std::array<double,3>({{1-half_eps,1,1}})),Point3d(std::array<double,3>({{1,1,1}}))));
	ASSERT_TRUE(lessEq(Point3d(std::array<double,3>({{1,1-half_eps,1}})),Point3d(std::array<double,3>({{1,1,1}}))));
	ASSERT_TRUE(lessEq(Point3d(std::array<double,3>({{1,1,1-half_eps}})),Point3d(std::array<double,3>({{1,1,1}}))));
	ASSERT_TRUE(lessEq(Point3d(std::array<double,3>({{1,1,1}})),Point3d(std::array<double,3>({{1-half_eps,1,1}}))));
	ASSERT_TRUE(lessEq(Point3d(std::array<double,3>({{1,1,1}})),Point3d(std::array<double,3>({{1,1-half_eps,1}}))));
	ASSERT_TRUE(lessEq(Point3d(std::array<double,3>({{1,1,1}})),Point3d(std::array<double,3>({{1,1,1-half_eps}}))));

	const double m(std::numeric_limits<double>::min());
	ASSERT_TRUE(lessEq(Point3d(std::array<double,3>({{m+half_eps,m,m}})),Point3d(std::array<double,3>({{m,m,m}}))));
	ASSERT_TRUE(lessEq(Point3d(std::array<double,3>({{m,m+half_eps,m}})),Point3d(std::array<double,3>({{m,m,m}}))));
	ASSERT_TRUE(lessEq(Point3d(std::array<double,3>({{m,m,m+half_eps}})),Point3d(std::array<double,3>({{m,m,m}}))));
	ASSERT_TRUE(lessEq(Point3d(std::array<double,3>({{m,m,m}})),Point3d(std::array<double,3>({{m+half_eps,m,m}}))));
	ASSERT_TRUE(lessEq(Point3d(std::array<double,3>({{m,m,m}})),Point3d(std::array<double,3>({{m,m+half_eps,m}}))));
	ASSERT_TRUE(lessEq(Point3d(std::array<double,3>({{m,m,m}})),Point3d(std::array<double,3>({{m,m,m+half_eps}}))));

	const double zero(0.0);
	ASSERT_TRUE(lessEq(Point3d(std::array<double,3>({{zero+half_eps,zero,zero}})),Point3d(std::array<double,3>({{zero,zero,zero}}))));
	ASSERT_TRUE(lessEq(Point3d(std::array<double,3>({{zero,zero+half_eps,zero}})),Point3d(std::array<double,3>({{zero,zero,zero}}))));
	ASSERT_TRUE(lessEq(Point3d(std::array<double,3>({{zero,zero,zero+half_eps}})),Point3d(std::array<double,3>({{zero,zero,zero}}))));
	ASSERT_TRUE(lessEq(Point3d(std::array<double,3>({{zero,zero,zero}})),Point3d(std::array<double,3>({{zero+half_eps,zero,zero}}))));
	ASSERT_TRUE(lessEq(Point3d(std::array<double,3>({{zero,zero,zero}})),Point3d(std::array<double,3>({{zero,zero+half_eps,zero}}))));
	ASSERT_TRUE(lessEq(Point3d(std::array<double,3>({{zero,zero,zero}})),Point3d(std::array<double,3>({{zero,zero,zero+half_eps}}))));

	ASSERT_TRUE(lessEq(Point3d(std::array<double,3>({{m+half_eps,m,m}})),Point3d(std::array<double,3>({{zero,zero,zero}}))));
	ASSERT_TRUE(lessEq(Point3d(std::array<double,3>({{m,m+half_eps,m}})),Point3d(std::array<double,3>({{zero,zero,zero}}))));
	ASSERT_TRUE(lessEq(Point3d(std::array<double,3>({{m,m,m+half_eps}})),Point3d(std::array<double,3>({{zero,zero,zero}}))));
	ASSERT_TRUE(lessEq(Point3d(std::array<double,3>({{m,m,m}})),Point3d(std::array<double,3>({{zero+half_eps,zero,zero}}))));
	ASSERT_TRUE(lessEq(Point3d(std::array<double,3>({{m,m,m}})),Point3d(std::array<double,3>({{zero,zero+half_eps,zero}}))));
	ASSERT_TRUE(lessEq(Point3d(std::array<double,3>({{m,m,m}})),Point3d(std::array<double,3>({{zero,zero,zero+half_eps}}))));

	ASSERT_TRUE(lessEq(Point3d(std::array<double,3>({{zero+half_eps,zero,zero}})),Point3d(std::array<double,3>({{m,m,m}}))));
	ASSERT_TRUE(lessEq(Point3d(std::array<double,3>({{zero,zero+half_eps,zero}})),Point3d(std::array<double,3>({{m,m,m}}))));
	ASSERT_TRUE(lessEq(Point3d(std::array<double,3>({{zero,zero,zero+half_eps}})),Point3d(std::array<double,3>({{m,m,m}}))));
	ASSERT_TRUE(lessEq(Point3d(std::array<double,3>({{zero,zero,zero}})),Point3d(std::array<double,3>({{m+half_eps,m,m}}))));
	ASSERT_TRUE(lessEq(Point3d(std::array<double,3>({{zero,zero,zero}})),Point3d(std::array<double,3>({{m,m+half_eps,m}}))));
	ASSERT_TRUE(lessEq(Point3d(std::array<double,3>({{zero,zero,zero}})),Point3d(std::array<double,3>({{m,m,m+half_eps}}))));

	ASSERT_TRUE(lessEq(Point3d(std::array<double,3>({{half_eps+half_eps,half_eps,half_eps}})),Point3d(std::array<double,3>({{half_eps,half_eps,half_eps}}))));
	ASSERT_TRUE(lessEq(Point3d(std::array<double,3>({{half_eps,half_eps+half_eps,zero}})),Point3d(std::array<double,3>({{half_eps,half_eps,half_eps}}))));
	ASSERT_TRUE(lessEq(Point3d(std::array<double,3>({{zero,zero,zero+half_eps}})),Point3d(std::array<double,3>({{half_eps,half_eps,half_eps}}))));
	ASSERT_TRUE(lessEq(Point3d(std::array<double,3>({{half_eps,half_eps,half_eps}})),Point3d(std::array<double,3>({{half_eps+half_eps,half_eps,half_eps}}))));
	ASSERT_TRUE(lessEq(Point3d(std::array<double,3>({{half_eps,half_eps,half_eps}})),Point3d(std::array<double,3>({{half_eps,half_eps+half_eps,half_eps}}))));
	ASSERT_TRUE(lessEq(Point3d(std::array<double,3>({{half_eps,half_eps,half_eps}})),Point3d(std::array<double,3>({{half_eps,half_eps,half_eps+half_eps}}))));

	ASSERT_TRUE(lessEq(Point3d(std::array<double,3>({{10.0+half_eps,10.0,10.0}})),Point3d(std::array<double,3>({{10.0,10.0,10.0}}))));
	ASSERT_TRUE(lessEq(Point3d(std::array<double,3>({{10.0,10.0+half_eps,10.0}})),Point3d(std::array<double,3>({{10.0,10.0,10.0}}))));
	ASSERT_TRUE(lessEq(Point3d(std::array<double,3>({{10.0,10.0,10.0+half_eps}})),Point3d(std::array<double,3>({{10.0,10.0,10.0}}))));
	ASSERT_TRUE(lessEq(Point3d(std::array<double,3>({{10.0,10.0,10.0}})),Point3d(std::array<double,3>({{10.0+half_eps,10.0,10.0}}))));
	ASSERT_TRUE(lessEq(Point3d(std::array<double,3>({{10.0,10.0,10.0}})),Point3d(std::array<double,3>({{10.0,10.0+half_eps,10.0}}))));
	ASSERT_TRUE(lessEq(Point3d(std::array<double,3>({{10.0,10.0,10.0}})),Point3d(std::array<double,3>({{10.0,10.0,10.0+half_eps}}))));
}

// test for operator==
TEST(MathLib, Point3dComparisonOperatorEqual)
{
	srand(static_cast<unsigned>(time(nullptr)));
	double x0(((double)(rand()) / RAND_MAX - 0.5));
	double x1(((double)(rand()) / RAND_MAX - 0.5));
	double x2(((double)(rand()) / RAND_MAX - 0.5));

	MathLib::Point3d a(std::array<double,3>({{x0, x1, x2}}));
	MathLib::Point3d b(std::array<double,3>({{x0, x1, x2}}));
	ASSERT_TRUE(a == b);
	ASSERT_TRUE((lessEq(a,b) && lessEq(b,a)) == (a == b));

	double tol(std::numeric_limits<double>::min());
	b[2] += tol;
	ASSERT_TRUE((lessEq(a, b) && lessEq(b, a)) == (a == b));
	b[1] = 0.0;
	b[2] = 0.0;
	ASSERT_TRUE((lessEq(a, b) && lessEq(b, a)) == (a == b));

	tol = std::numeric_limits<double>::epsilon();
	ASSERT_FALSE(Point3d(std::array<double,3>({{tol,1.0,1.0}})) == Point3d(std::array<double,3>({{1.0,1.0,1.0}})));
	ASSERT_FALSE(Point3d(std::array<double,3>({{1.0,tol,1.0}})) == Point3d(std::array<double,3>({{1.0,1.0,1.0}})));
	ASSERT_FALSE(Point3d(std::array<double,3>({{1.0,1.0,tol}})) == Point3d(std::array<double,3>({{1.0,1.0,1.0}})));

	ASSERT_FALSE(Point3d(std::array<double,3>({{1.0,1.0,1.0}})) == Point3d(std::array<double,3>({{1.0+tol,1.0,1.0}})));
	ASSERT_FALSE(Point3d(std::array<double,3>({{1.0,1.0,1.0}})) == Point3d(std::array<double,3>({{1.0,1.0+tol,1.0}})));
	ASSERT_FALSE(Point3d(std::array<double,3>({{1.0,1.0,1.0}})) == Point3d(std::array<double,3>({{1.0,1.0,1.0+tol}})));

	// very small difference in one coordinate
	tol = std::numeric_limits<double>::min();
	ASSERT_TRUE(Point3d(std::array<double,3>({{tol,0.0,0.0}})) == Point3d(std::array<double,3>({{0.0,0.0,0.0}})));
	ASSERT_TRUE(Point3d(std::array<double,3>({{0.0,tol,0.0}})) == Point3d(std::array<double,3>({{0.0,0.0,0.0}})));
	ASSERT_TRUE(Point3d(std::array<double,3>({{0.0,0.0,tol}})) == Point3d(std::array<double,3>({{0.0,0.0,0.0}})));

	ASSERT_TRUE(Point3d(std::array<double,3>({{0.0,0.0,0.0}})) == Point3d(std::array<double,3>({{tol,0.0,0.0}})));
	ASSERT_TRUE(Point3d(std::array<double,3>({{0.0,0.0,0.0}})) == Point3d(std::array<double,3>({{0.0,tol,0.0}})));
	ASSERT_TRUE(Point3d(std::array<double,3>({{0.0,0.0,0.0}})) == Point3d(std::array<double,3>({{0.0,0.0,tol}})));

	a = Point3d(std::array<double,3>({{0.0,0.0,0.0}}));
	b = Point3d(std::array<double,3>({{0.0,0.0,0.0}}));
	a[0] = pow(std::numeric_limits<double>::epsilon(),5);
	ASSERT_TRUE((lessEq(a,b) && lessEq(b,a)) == (a == b));
}

// test for operator<
TEST_F(MathLibPoint3d, ComparisonOperatorLess)
{
	// A point is never less than itself or its copy.
	auto samePointLessCompare = [](MathLib::Point3d const& p)
	{
		auto q = p;
		return !(p < p) && !(p < q) && !(q < p);
	};

	ac::check<MathLib::Point3d>(samePointLessCompare, 100,
								ac::make_arbitrary(pointGenerator),
								gtest_reporter);


	// A point with any positive value added to one of its coordinates is
	// always larger then the original point.
	auto pointWithAddedValue = [](MathLib::Point3d const& p, double const eps,
								  unsigned const coordinate)
	{
		auto q = p;
		q[coordinate] = q[coordinate] + eps;
		return (p < q) && !(q < p);
	};

	ac::check<MathLib::Point3d, double, unsigned>(
		pointWithAddedValue, 1000,
		ac::make_arbitrary(
			pointGenerator,
			ac::map(&ac::absoluteValue<double>, ac::generator<double>()),
			ac::map(&ac::mod3, ac::generator<unsigned>())	// any of {0,1,2}
			)
			.discard_if(
				[](MathLib::Point3d const&, double const eps, unsigned const)
				{
					return eps == 0;
				}),
		gtest_reporter);

	// A point with any positive value subtracted from one of its coordinates is
	// always smaller then the original point.
	auto pointWithSubtractedValue = [](
		MathLib::Point3d const& p, double const eps, unsigned const coordinate)
	{
		auto q = p;
		q[coordinate] = q[coordinate] - eps;
		return (q < p) && !(p < q);
	};

	ac::check<MathLib::Point3d, double, unsigned>(
		pointWithSubtractedValue, 1000,
		ac::make_arbitrary(
			pointGenerator,
			ac::map(&ac::absoluteValue, ac::generator<double>()),
			ac::map(&ac::mod3, ac::generator<unsigned>())  // any of {0,1,2}
			)
			.discard_if(
				[](MathLib::Point3d const&, double const eps, unsigned const)
				{
					return eps == 0;
				}),
		gtest_reporter);
}
