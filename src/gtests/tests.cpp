#include <iostream>

#include <gtest/gtest.h>

#include <TH1D.h>

#include <a4/root_object_store.h>
using a4::store::RootObjectStore;
using a4::store::ObjectStore;
using a4::store::RTH1D;
using a4::store::RTH2D;

const size_t GRIND_REPETITIONS = 1000000;

TEST(a4store, plain_10_th1d) {
    TH1D h10("test0", "test", 100, 0, 100);
    TH1D h11("test1", "test", 100, 0, 100);
    TH1D h12("test2", "test", 100, 0, 100);
    TH1D h13("test3", "test", 100, 0, 100);
    TH1D h14("test4", "test", 100, 0, 100);
    TH1D h15("test5", "test", 100, 0, 100);
    TH1D h16("test6", "test", 100, 0, 100);
    TH1D h17("test7", "test", 100, 0, 100);
    TH1D h18("test8", "test", 100, 0, 100);
    TH1D h19("test9", "test", 100, 0, 100);
    for (size_t i = 0; i < GRIND_REPETITIONS; i++) {
        h10.Fill((i+0) % 100);
        h11.Fill((i+1) % 100);
        h12.Fill((i+2) % 100);
        h13.Fill((i+3) % 100);
        h14.Fill((i+4) % 100);
        h15.Fill((i+5) % 100);
        h16.Fill((i+6) % 100);
        h17.Fill((i+7) % 100);
        h18.Fill((i+8) % 100);
        h19.Fill((i+9) % 100);
    }
}

TEST(a4store, plain_10_th2d) {
    TH2D h20("test0", "test", 100, 0, 100, 100, 0, 100);
    TH2D h21("test1", "test", 100, 0, 100, 100, 0, 100);
    TH2D h22("test2", "test", 100, 0, 100, 100, 0, 100);
    TH2D h23("test3", "test", 100, 0, 100, 100, 0, 100);
    TH2D h24("test4", "test", 100, 0, 100, 100, 0, 100);
    TH2D h25("test5", "test", 100, 0, 100, 100, 0, 100);
    TH2D h26("test6", "test", 100, 0, 100, 100, 0, 100);
    TH2D h27("test7", "test", 100, 0, 100, 100, 0, 100);
    TH2D h28("test8", "test", 100, 0, 100, 100, 0, 100);
    TH2D h29("test9", "test", 100, 0, 100, 100, 0, 100);
    for (size_t i = 0; i < GRIND_REPETITIONS; i++) {
        h20.Fill((i+0) % 100, (10+i+0) % 100);
        h21.Fill((i+1) % 100, (10+i+1) % 100);
        h22.Fill((i+2) % 100, (10+i+2) % 100);
        h23.Fill((i+3) % 100, (10+i+3) % 100);
        h24.Fill((i+4) % 100, (10+i+4) % 100);
        h25.Fill((i+5) % 100, (10+i+5) % 100);
        h26.Fill((i+6) % 100, (10+i+6) % 100);
        h27.Fill((i+7) % 100, (10+i+7) % 100);
        h28.Fill((i+8) % 100, (10+i+8) % 100);
        h29.Fill((i+9) % 100, (10+i+9) % 100);
    }
}

TEST(a4store, a4store_10_th1d) {
    RootObjectStore backstore;
    ObjectStore S = backstore.store();
    
    for (size_t i = 0; i < GRIND_REPETITIONS; i++) {
        for (int j = 0; j < 10; j++) {
        //int j = 0;
            S.T<RTH1D>("test", j)(100, 0., 100.).fill((i+j) % 100); //j += 1;
            /*
        S.T<RTH1D>("test1")(100, 0., 100.).fill((i+j) % 100); j += 1;
        S.T<RTH1D>("test2")(100, 0., 100.).fill((i+j) % 100); j += 1;
        S.T<RTH1D>("test3")(100, 0., 100.).fill((i+j) % 100); j += 1;
        S.T<RTH1D>("test4")(100, 0., 100.).fill((i+j) % 100); j += 1;
        S.T<RTH1D>("test5")(100, 0., 100.).fill((i+j) % 100); j += 1;
        S.T<RTH1D>("test6")(100, 0., 100.).fill((i+j) % 100); j += 1;
        S.T<RTH1D>("test7")(100, 0., 100.).fill((i+j) % 100); j += 1;
        S.T<RTH1D>("test8")(100, 0., 100.).fill((i+j) % 100); j += 1;
        S.T<RTH1D>("test9")(100, 0., 100.).fill((i+j) % 100);
        */
        }
    }
}

TEST(a4store, a4store_10_th2d) {
    RootObjectStore backstore;
    ObjectStore S = backstore.store();
    
    for (size_t i = 0; i < GRIND_REPETITIONS; i++) {
        for (int j = 0; j < 10; j++) {
            S.T<RTH2D>("test", j)
                (100, 0., 100.)
                (100, 0., 100.)
                .fill((i+j) % 100, (10+i+j) % 100);
        }
    }
}

/*
class MinimalistPrinter : public ::testing::EmptyTestEventListener {
    // Called before a test starts.
    virtual void OnTestStart(const ::testing::TestInfo& test_info) {
        printf("*** Test %s.%s starting.\n",
        test_info.test_case_name(), test_info.name());
    }

    // Called after a failed assertion or a SUCCEED() invocation.
    virtual void OnTestPartResult(
        const ::testing::TestPartResult& test_part_result) {
        printf("%s in %s:%d\n%s\n",
        test_part_result.failed() ? "*** Failure" : "Success",
        test_part_result.file_name(),
        test_part_result.line_number(),
        test_part_result.summary());
    }

    // Called after a test ends.
    virtual void OnTestEnd(const ::testing::TestInfo& test_info) {
        printf("*** Test %s.%s ending.\n",
        test_info.test_case_name(), test_info.name());
    }
};
*/

class Environment : public ::testing::Environment {
    public:
    virtual ~Environment() {}
    virtual void SetUp() {
        /*
        ::testing::TestEventListeners& listeners =
            ::testing::UnitTest::GetInstance()->listeners();
        listeners.Append(new MinimalistPrinter);
        */
    }
    virtual void TearDown() {
        std::map<std::string, float> time_map;
        const auto* ut = ::testing::UnitTest::GetInstance();
        for (int i = 0; i < ut->total_test_case_count(); i++) {
            const auto* tc = ut->GetTestCase(i);
            for (int j = 0; j < tc->total_test_count(); j++) {
                const auto* ti = tc->GetTestInfo(j);
                const auto* tr = ti->result();
                time_map[ti->name()] = tr->elapsed_time();
            }
        }
        
        std::cout << "10 x 1D hist time(a4store) / time(root) = "
                  << time_map["a4store_10_th1d"] / time_map["plain_10_th1d"]
                  << std::endl;
                  
        std::cout << "10 x 2D hist time(a4store) / time(root) = "
                  << time_map["a4store_10_th2d"] / time_map["plain_10_th2d"]
                  << std::endl;
    }
};

class MakeEnv {
public:
    MakeEnv() { ::testing::AddGlobalTestEnvironment(new Environment); }
    ~MakeEnv() {
        //std::cout << "Finalization" << std::endl;
    }
};
static MakeEnv make_env;
