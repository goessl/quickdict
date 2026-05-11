from quickdict import *



def test_qd_pos():
    assert qd_pos({}) == {}
    assert qd_pos({0:1, 2:-3}) == {0:+1, 2:-3}

def test_qd_ipos():
    m = {}
    qd_ipos(m)
    assert m == {}
    
    m = {0:1, 2:-3}
    qd_ipos(m)
    assert m == {0:+1, 2:-3}


def test_qd_neg():
    assert qd_neg({}) == {}
    assert qd_neg({0:1, 2:-3}) == {0:-1, 2:+3}

def test_qd_ineg():
    m = {}
    qd_ineg(m)
    assert m == {}
    
    m = {0:1, 2:-3}
    qd_ineg(m)
    assert m == {0:-1, 2:+3}
