#include "catch.hpp"
#include "../point.hpp"
#include "../quickhull_single_thead/convex_hull_solver.h"
#include "../quickhull_parallel/convex_hull_solver_parallel.hpp"
#include "../quickhull_parallel_future/convex_hull_solver_parallel_future.hpp"
void compare_result(std::vector<point>& expected, std::vector<point>& actual);

void compare_result(std::vector<point>& expected, std::vector<point>& actual){
    bool found_in_result = false;
    REQUIRE(expected.size() == actual.size());
    for (point expected_point : expected){ // Check that all expected points are present in the actual
        for (point actual_point : actual){
            if (actual_point.x == expected_point.x && actual_point.y == expected_point.y) {
                found_in_result = true;
                break;
            }
        }
        REQUIRE(found_in_result);
        found_in_result = false;
    }
}

/**
 * I compare the results of my algorithm with results i got from this online calculator.
 * The sets i use are randomly generated by my points generator.
 * https://planetcalc.com/8576/
 */
TEST_CASE("Quickhull 20 points"){
    std::vector<point> inputs = {
            point(474,533),
           point(15,767),
          point(0,644),
            point(171,582),
            point(961,420),
            point(289,814),
            point(583,269),
           point(46,136),
            point(108,935),
           point(36,447),
            point(726,339),
            point(774,391),
            point(152,1),
            point(321,579),
            point(535,770),
           point(17,351),
            point(259,178),
            point(406,542),
            point(216,331),
            point(551,33)
    };

    std::vector<point> convex_hull = {
            point(152, 1),
            point(551, 33),
            point(961, 420),
            point(535, 770),
            point(108, 935),
            point(15, 767),
            point(0, 644),
            point(17, 351),
            point(46, 136),
    };

    SECTION("Single-thread"){
        convex_hull_solver solver = convex_hull_solver(inputs);
        std::vector<point> result = solver.quickhull();
        compare_result(convex_hull, result);
    }

    SECTION("Multi-thread-mutex"){
        convex_hull_solver_parallel solver = convex_hull_solver_parallel(inputs, 4);
        std::vector<point> result = solver.quickhull_parallel();
        compare_result(convex_hull, result);
    }

    SECTION("Multi-thread-future"){
        convex_hull_solver_parallel_future solver = convex_hull_solver_parallel_future(inputs, 4);
        std::vector<point> result = solver.quickhull_parallel();
        compare_result(convex_hull, result);
    }
}

TEST_CASE("Quickhull 50 points"){
    std::vector<point> inputs = {
            point(489,195),
            point(740,421),
            point(703,225),
            point(960,399),
            point(683,711),
            point(847,465),
            point(862,392),
            point(815,813),
            point(296,274),
            point(973,996),
            point(762,406),
            point(351,416),
            point(895,608),
            point(699,554),
            point(893,16),
            point(310,25),
            point(20,658),
            point(326,936),
            point(592,265),
            point(282,574),
            point(809,313),
            point(925,13),
            point(645,874),
            point(790,517),
            point(779,921),
            point(763,199),
            point(212,942),
            point(373,723),
            point(916,19),
            point(98,484),
            point(793,468),
            point(156,687),
            point(869,231),
            point(553,434),
            point(362,202),
            point(708,786),
            point(310,676),
            point(362,996),
            point(849,354),
            point(265,984),
            point(393,853),
            point(521,758),
            point(547,500),
            point(113,535),
            point(116,105),
            point(989,529),
            point(140,367),
            point(779,184),
            point(563,233),
            point(685,930),
            };

    std::vector<point> convex_hull = {
            point(925, 13),
            point(989, 529),
            point(973, 996),
            point(362, 996),
            point(265, 984),
            point(212, 942),
            point(20, 658),
            point(116, 105),
            point(310, 25),
    };

    SECTION("Single-thread"){
        convex_hull_solver solver = convex_hull_solver(inputs);
        std::vector<point> result = solver.quickhull();
        compare_result(convex_hull, result);
    }

    SECTION("Multi-thread-mutex"){
        convex_hull_solver_parallel solver = convex_hull_solver_parallel(inputs, 4);
        std::vector<point> result = solver.quickhull_parallel();
        compare_result(convex_hull, result);
    }

    SECTION("Multi-thread-future"){
        convex_hull_solver_parallel_future solver = convex_hull_solver_parallel_future(inputs, 4);
        std::vector<point> result = solver.quickhull_parallel();
        compare_result(convex_hull, result);
    }
}

TEST_CASE("Quickhull 100 points"){
    std::vector<point> inputs = {
           point( 352,581),
           point( 448,679),
           point( 983,122),
           point( 278,213),
           point( 375,252),
           point( 212,532),
           point( 868,823),
           point( 949,610),
          point(  31,20),
           point( 888,967),
           point( 593,197),
           point( 325,119),
           point( 168,859),
           point( 146,54),
           point( 478,500),
          point(  63,447),
           point( 260,495),
           point( 195,824),
           point( 253,704),
           point( 321,452),
           point( 966,18),
           point( 425,62),
           point( 519,266),
           point( 338,419),
           point( 346,381),
           point( 931,895),
           point( 971,272),
           point( 867,350),
           point( 920,797),
           point( 554,772),
           point( 617,259),
           point( 557,81),
           point( 462,144),
           point( 867,22),
           point( 255,653),
           point( 193,713),
           point( 970,712),
           point( 481,512),
           point( 297,213),
           point( 807,617),
           point( 605,882),
           point( 727,660),
           point( 359,189),
           point( 713,692),
           point( 815,583),
           point( 726,914),
           point( 709,86),
           point( 433,692),
           point( 186,184),
           point( 890,206),
           point( 738,67),
         point(   5,430),
           point( 342,683),
           point( 595,900),
          point(  16,691),
           point( 774,533),
           point( 740,856),
           point( 382,116),
           point( 463,829),
          point(  90,347),
           point( 247,524),
           point( 833,413),
           point( 269,196),
           point( 438,653),
           point( 229,521),
           point( 965,518),
          point(  76,985),
           point( 597,844),
           point( 133,784),
          point(  99,793),
           point( 222,33),
            point(1000,184),
           point( 954,193),
           point( 865,624),
           point( 545,90),
           point( 225,340),
           point( 100,500),
           point( 401,469),
          point(  15,389),
          point(  43,7),
           point( 566,666),
           point( 736,142),
           point( 559,884),
           point( 939,959),
           point( 873,395),
           point( 265,69),
           point( 515,286),
           point( 398,446),
           point( 469,309),
           point( 159,540),
          point(  43,91),
          point(  32,978),
           point( 175,43),
           point( 721,203),
           point( 831,694),
           point( 866,706),
           point( 859,179),
           point( 269,179),
           point( 975,531),
           point( 181,221)
    };

    std::vector<point> convex_hull = {
            point(43, 7),
            point(966, 18),
            point(1000, 184),
            point(970, 712),
            point(939, 959),
            point(888, 967),
            point(76, 985),
            point(32, 978),
            point(16, 691),
            point(5, 430),
            point(31, 20)
    };

    SECTION("Single-thread"){
        convex_hull_solver solver = convex_hull_solver(inputs);
        std::vector<point> result = solver.quickhull();
        compare_result(convex_hull, result);
    }

    SECTION("Multi-thread-mutex"){
        convex_hull_solver_parallel solver = convex_hull_solver_parallel(inputs, 4);
        std::vector<point> result = solver.quickhull_parallel();
        compare_result(convex_hull, result);
    }

    SECTION("Multi-thread-future"){
        convex_hull_solver_parallel_future solver = convex_hull_solver_parallel_future(inputs, 4);
        std::vector<point> result = solver.quickhull_parallel();
        compare_result(convex_hull, result);
    }
}
