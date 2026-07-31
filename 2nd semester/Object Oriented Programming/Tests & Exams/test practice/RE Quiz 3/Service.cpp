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

void Service::addQuestion(int id, const std::string& txt, const std::string& ans, int sc)
{
    if (txt.empty()) throw std::runtime_error("Question text cannot be empty");
    for (auto& i : this->getAllID())
    {
        if (i.getId() == id) throw std::runtime_error("Question with this id exists");
    }
    Question q(id, txt, ans, sc);
    repo.addQuestion(q);
    notifyObs();
}

bool Service::correctAns(int id, const std::string& ans)
{
    bool found = false; 
    for (auto& q : this->getAllID())
    {
        if (q.getId() == id)
        {
            found = true;
            if (q.getAnswer() == ans) return true;
        }
    }
    if (found == false) throw std::runtime_error("Not a valid question");
    return false; 
}

int Service::getScoreById(int id)
{
    for (auto& q : getAllID())
    {
        if (q.getId() == id) return q.getScore();
    }
    return 0; 
}
