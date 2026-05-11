from quickdict import *



def test_qd_filter():
    assert qd_filter({}) == {}
    assert qd_filter({1:0, 2:3}) == {2:3}

def test_qd_ifilter():
    m = {}
    qd_ifilter(m)
    assert m == {}
    
    m = {1:0, 2:3}
    qd_ifilter(m)
    assert m == {2:3}
