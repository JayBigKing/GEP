from enum import Enum
import numpy as np
theMaxReal:float = np.sys.float_info.max
dangerousVal:float = theMaxReal * 1e-50
class WhichFunction(Enum):
    W_add = 0
    W_minus = 1
    W_times = 2
    W_divide = 3
    W_sin = 4
    W_cos = 5
    W_tan = 6
    W_asin = 7
    W_acos = 8
    W_atan = 9
    W_atan2 = 10
    W_pow = 11
    W_square = 12
    W_cube = 13
    W_sqrt = 14
    W_log2 = 15
    W_log10 = 16
    W_max = 17
    W_min = 18
    W_ex = 19

functionArgMap = {WhichFunction.W_add:(2,"add"),WhichFunction.W_minus:(2,"miuns"),
                  WhichFunction.W_times:(2,"times"),WhichFunction.W_divide:(2,"divide"),
                  WhichFunction.W_sin:(1,"sin"),WhichFunction.W_cos:(1,"cos"),
                  WhichFunction.W_tan:(1,"tan"),WhichFunction.W_asin:(1,"asin"),
                  WhichFunction.W_acos:(1,"acos"),WhichFunction.W_atan:(1,"atan"),
                  WhichFunction.W_atan2:(2,"atan2"),WhichFunction.W_pow:(2,"pow"),
                  WhichFunction.W_square:(1,"square"),WhichFunction.W_cube:(1,"cube"),
                  WhichFunction.W_sqrt:(1,"sqrt"),WhichFunction.W_log2:(1,"log2"),
                  WhichFunction.W_log10:(1,"log10"),WhichFunction.W_max:(2,"max"),
                  WhichFunction.W_min:(2,"min"),WhichFunction.W_ex:(1,"exp")}



functionNumVec = [WhichFunction.W_add,WhichFunction.W_minus,
                  WhichFunction.W_times,WhichFunction.W_divide,
                  WhichFunction.W_sin,WhichFunction.W_cos,
                  WhichFunction.W_tan,WhichFunction.W_asin,
                  WhichFunction.W_acos,WhichFunction.W_atan,
                  WhichFunction.W_atan2,WhichFunction.W_pow,
                  WhichFunction.W_square,WhichFunction.W_cube,
                  WhichFunction.W_sqrt,WhichFunction.W_log2,
                  WhichFunction.W_log10,WhichFunction.W_max,
                  WhichFunction.W_min,WhichFunction.W_ex]




def addHandler(args):
    return args[0] + args[1]
def miusHandler(args):
    return args[0] - args[1]
def timesHandler(args):
    return args[0] * args[1]
def divideHandler(args):
    if abs(args[1]) < 1e-5:
        return theMaxReal
    else:
        outVal = args[0] / args[1]
        if np.isfinite(outVal) == False:
            return theMaxReal
        else:
            return outVal
def sinHandler(args):
    return np.sin(args[0])
def cosHandler(args):
    return np.cos(args[0])
def tanHandler(args):
    outVal = np.tan(args[0])
    if np.isinf(outVal) or outVal >= dangerousVal:
        return theMaxReal
    else:
        return outVal
def asinHandler(args):
    if args[0] > 1 or args[0] < -1:
        return theMaxReal
    else:
        return np.arcsin(args[0])
def acosHandler(args):
    if args[0] > 1 or args[0] < -1:
        return theMaxReal
    else:
        return np.arccos(args[0])
def atanHandler(args):
    return np.arctan(args[0])
def atan2Handler(args):
    if args[1] < 1e-5:
        return theMaxReal
    else:
        outVal = np.arctan2(args[0], args[1])
        if np.isinf(outVal):
            return theMaxReal
        else:
            return outVal

def powHandler(args):
    return np.power(args[0], args[1])
def squareHandler(args):
    return np.square(args[0])
def cubeHandler(args):
    return np.power(args[0],3)
def sqrtHandler(args):
    return np.sqrt(args[0])
def log2Handler(args):
    outVal = np.log2(args[0])
    if np.isnan(outVal):
        return theMaxReal
    else:
        return outVal
def log10Handler(args):
    outVal = np.log10(args[0])
    if np.isnan(outVal):
        return theMaxReal
    else:
        return outVal
def maxHandler(args):
    return np.max(args[0],args[1])
def minHandler(args):
    return np.min(args[0],args[1])
def expHandler(args):
    outVal = np.exp(args[0])
    if np.isinf(outVal) or outVal >= dangerousVal:
        return theMaxReal
    else:
        return outVal




functionHandlerMap = {WhichFunction.W_add:addHandler,WhichFunction.W_minus:miusHandler,
                  WhichFunction.W_times:timesHandler,WhichFunction.W_divide:divideHandler,
                  WhichFunction.W_sin:sinHandler,WhichFunction.W_cos:cosHandler,
                  WhichFunction.W_tan:tanHandler,WhichFunction.W_asin:asinHandler,
                  WhichFunction.W_acos:acosHandler,WhichFunction.W_atan:atanHandler,
                  WhichFunction.W_atan2:atan2Handler,WhichFunction.W_pow:powHandler,
                  WhichFunction.W_square:squareHandler,WhichFunction.W_cube:cubeHandler,
                  WhichFunction.W_sqrt:sqrtHandler,WhichFunction.W_log2:log2Handler,
                  WhichFunction.W_log10:log10Handler,WhichFunction.W_max:maxHandler,
                  WhichFunction.W_min:minHandler,WhichFunction.W_ex:expHandler}

def functionPresetHandler(args,whichFunction):
    return functionHandlerMap[whichFunction](args)
    # try:
    #     if whichFunction == WhichFunction.W_add:
    #         return args[0] + args[1]
    #     elif whichFunction == WhichFunction.W_minus:
    #         return args[0] - args[1]
    #     elif whichFunction == WhichFunction.W_times:
    #         return args[0] * args[1]
    #     elif whichFunction == WhichFunction.W_divide:
    #         if abs(args[1]) < 1e-5:
    #             return theMaxReal
    #         else:
    #             outVal = args[0] / args[1]
    #             if np.isfinite(outVal) == False:
    #                 return theMaxReal
    #             else:
    #                 return outVal
    #     elif whichFunction == WhichFunction.W_sin:
    #         return np.sin(args[0])
    #     elif whichFunction == WhichFunction.W_cos:
    #         return np.cos(args[0])
    #     elif whichFunction == WhichFunction.W_tan:
    #         outVal = np.tan(args[0])
    #         if np.isinf(outVal) or outVal >= dangerousVal:
    #             return theMaxReal
    #         else:
    #             return outVal
    #     elif whichFunction == WhichFunction.W_asin:
    #         if args[0] > 1 or args[0] < -1:
    #             return theMaxReal
    #         else:
    #             return np.arcsin(args[0])
    #     elif whichFunction == WhichFunction.W_acos:
    #         if args[0] > 1 or args[0] < -1:
    #             return theMaxReal
    #         else:
    #             return np.arccos(args[0])
    #     elif whichFunction == WhichFunction.W_atan:
    #         return np.arctanh(args[0])
    #     elif whichFunction == WhichFunction.W_atan2:
    #         if args[1] < 1e-5:
    #             return theMaxReal
    #         else:
    #             outVal = np.arctan2(args[0],args[1])
    #             if np.isinf(outVal):
    #                 return theMaxReal
    #             else:
    #                 return outVal
    #     elif whichFunction == WhichFunction.W_pow:
    #         return np.power(args[0],args[1])
    #     elif whichFunction == WhichFunction.W_square:
    #         return np.power(args[0] , 2)
    #     elif whichFunction == WhichFunction.W_cube:
    #         return np.power(args[0],3)
    #     elif whichFunction == WhichFunction.W_sqrt:
    #         return np.sqrt(args[0])
    #     elif whichFunction == WhichFunction.W_log2:
    #         outVal = np.log2(args[0])
    #         if np.isnan(outVal):
    #             return theMaxReal
    #         else:
    #             return outVal
    #     elif whichFunction == WhichFunction.W_log10:
    #         outVal = np.log10(args[0])
    #         if np.isnan(outVal):
    #             return theMaxReal
    #         else:
    #             return outVal
    #     elif whichFunction == WhichFunction.W_max:
    #         return np.max(args[0],args[1])
    #     elif whichFunction == WhichFunction.W_min:
    #         return np.min(args[0],args[1])
    #     elif whichFunction == WhichFunction.W_ex:
    #         outVal = np.exp(args[0])
    #         if np.isinf(outVal) or outVal >= dangerousVal:
    #             return theMaxReal
    #         else:
    #             return outVal
    #     else:
    #         raise ValueError("error : no such function which is preseted!")
    # except ValueError as e:
    #     print(repr(e))
    #     exit(-1)

def getTheMaxReal():
    return theMaxReal

def getTheDangerousReal():
    return dangerousVal

def ifValDangerous(x):
    if x == theMaxReal:
        return True
    elif np.isfinite(x):
        return False
    else:
        return True