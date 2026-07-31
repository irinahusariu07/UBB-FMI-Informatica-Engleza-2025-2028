#include"ParticipantWindow.h"
#include"PresenterWindow.h"
#include"Participant.h"
#include <QtWidgets/QApplication>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    Repo repo{ "questions.txt", "participants.txt" };
    Service service{ repo };

    auto* prWin = new PresenterWindow(service);
    prWin->show();

    for (auto& p : repo.getParticipants())
    {
        auto* paWin = new ParticipantWindow(service, p);
        paWin->show();
    }

    return app.exec();
}
