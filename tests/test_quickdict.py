from quickdict import *



def test_qd_pos():
    assert qd_pos({}) == {}
    assert qd_pos({0:1, 2:-3}) == {0:+1, 2:-3}


def test_qd_neg():
    assert qd_neg({}) == {}
    assert qd_neg({0:1, 2:-3}) == {0:-1, 2:+3}
