#include <iostream>
#include <string>

#include <QVector>
#include <QString>

#include "studentdatainfo.h"

int main()
{
    StudentDataInfo studInfoCmd;

    std::string command;
    do {
        std::cout << "\nEnter one of the following commands: \n"
                  << "  list  - display previously loaded or created student data\n"
                  << "  new   - create a new student data\n"
                  << "  load  - deserialize student data into memory\n"
                  << "  write - serialize student data to files\n"
                  << "  exit  - exit the program\n\n";

        std::cin >> command;
        studInfoCmd.execute(QString::fromStdString(command));

    } while (command != "exit");
}
