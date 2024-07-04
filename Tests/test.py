import random

import pd

COUPLING_NUMBER = 0.4
OLDNUMBER = 0.4 
OLDDIV = 100000
MELHORDIV = 100000


def bestvalue():
    global COUPLING_NUMBER
    arrayDiv = pd.tabread("div")
    bpmMedia = pd.tabread("follower")
    bpm = sum(bpmMedia) / len(bpmMedia)
    print("BPM:", bpm)
    Divergencia = sum(arrayDiv) / len(arrayDiv)
    if Divergencia < OLDDIV:
        if Divergencia < MELHORDIV:
            print("Melhor valor:", COUPLING_NUMBER)
    
    COUPLING_NUMBER = random.uniform(0, 1)
    return COUPLING_NUMBER

    

    








def test_setup():
    pd.add_object(bestvalue, "py.b")
