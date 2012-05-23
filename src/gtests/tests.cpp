#include <iostream>

#include <gtest/gtest.h>

#include <a4/root_object_store.h>
using a4::store::RootObjectStore;
using a4::store::ObjectStore;
using a4::store::RTH1;

const size_t GRIND_REPETITIONS = 50000000;

TEST(a4store, test_th1d_many) {
    TH1D h10("test0", "test", 100, 0, 1);
    TH1D h11("test1", "test", 100, 0, 1);
    TH1D h12("test2", "test", 100, 0, 1);
    TH1D h13("test3", "test", 100, 0, 1);
    TH1D h14("test4", "test", 100, 0, 1);
    TH1D h15("test5", "test", 100, 0, 1);
    TH1D h16("test6", "test", 100, 0, 1);
    TH1D h17("test7", "test", 100, 0, 1);
    TH1D h18("test8", "test", 100, 0, 1);
    TH1D h19("test9", "test", 100, 0, 1);
    for (size_t i = 0; i < GRIND_REPETITIONS / 10; i++) {
        h10.Fill(i+0);
        h11.Fill(i+1);
        h12.Fill(i+2);
        h13.Fill(i+3);
        h14.Fill(i+4);
        h15.Fill(i+5);
        h16.Fill(i+6);
        h17.Fill(i+7);
        h18.Fill(i+8);
        h19.Fill(i+9);
    }
}

TEST(a4store, basic_test) {
    RootObjectStore backstore;
    ObjectStore S = backstore.store();
    
    // TODO
    //S.T<RTH1>("test/test/blah")(100, 0., 100.).fill(100);
}
