#pragma once

enum class ATMMessage 
{ 
    Success = 1, 
    LackBalance = -1, 
    LackCache = -2,
    InvalidNumber = -3,
    UnknownCustommer = -4
};