#include "Service.h"

std::vector<Question> Service::getAllID()
{
    std::vector<Question> result = repo.getQuestion(); 
    std::sort(result.begin(), result.end(), [&](Question q1, Question q2)
        {
            return q1.getId() < q2.getId();
        });
    return result; 
}


std::vector<Question> Service::getAllScore()
{
    std::vector<Question> result = repo.getQuestion();
    std::sort(result.begin(), result.end(), [&](Question q1, Question q2)
        {
            return q1.getScore() > q2.getScore();
        });
    return result;
}