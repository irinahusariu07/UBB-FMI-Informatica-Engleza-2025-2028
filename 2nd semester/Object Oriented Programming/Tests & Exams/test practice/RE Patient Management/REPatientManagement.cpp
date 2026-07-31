#include "REPatientManagement.h"

REPatientManagement::REPatientManagement(Service& srv, const std::string& doc, QWidget* parent)
    : QMainWindow(parent), service{ srv }, doctor{ doc }
{
    ui.setupUi(this);
    this->setWindowTitle(QString::fromStdString(doctor));
    service.addObserver(this);
    ui.label->setText(QString::fromStdString("Doctor: " + doctor));
    std::string curr_spec = service.getDocByName(doctor);
    model = new PatientModel(service.sortByDates(service.getSpecialisationPatients(curr_spec)), doctor);
    ui.tableView->setModel(model);

    connect(ui.addBtn, &QPushButton::clicked, this, [=]() {
        std::string pn, pd, ps, pdoc, pdate;
        pn = ui.nameInput->text().toStdString();
        pd = ui.diagnosisInput->text().toStdString();
        ps = ui.specialisationInput->text().toStdString();
        pdoc = ui.docInput->text().toStdString();
        pdate = ui.dateInput->text().toStdString();
        try
        {
            service.addPatient(pn, pd, ps, pdoc, pdate);
        }
        catch (std::exception& e)
        {
            QMessageBox::critical(this, "Error: ", e.what());
        }

        });

    connect(ui.checkBox, &QCheckBox::stateChanged, this, [=](int state) {
        std::vector<Patient> display;
        if (state == Qt::Checked) display = service.getDocNamePatients(doctor);
        else display = service.sortByDates(service.getSpecialisationPatients(curr_spec));
        model->updateData(display);
        });

    connect(ui.updateBtn, &QPushButton::clicked, this, [=]() {
        std::string pn, pd, ps;
        pn = ui.nameInput->text().toStdString();
        pd = ui.diagnosisInput->text().toStdString();
        ps = ui.specialisationInput->text().toStdString();
        try
        {
            service.updatePatient(pn, doctor, pd, ps);
        }
        catch (std::exception& e)
        {
            QMessageBox::critical(this, "Error: ", e.what());
        }
        });
}

REPatientManagement::~REPatientManagement()
{}

