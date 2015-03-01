/* Print "Hello World" to stdout. */

#include <QTextStream>

QTextStream out(stdout);

int main(void) {
  out << "Hello World" << endl;  
}
