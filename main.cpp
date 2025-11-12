// Создать приложение для чтения из файла данных и записи их в другой файл в
// другом формате. Используйте структуры.
//
// ### Исходный файл
// ```
// Family1|Name1
// Famyly2|Name2
// ```
//
// ### Получаемый файл
// ```
// Family1
// Family2
// ```

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// Структуры ++
struct Parsed_line {
  std::string name;
  std::string surname;
};
// Структуры--

// Функции++

// TODO Сделать функцию ParseLineIntoVector универсальной

std::vector<std::string> ParseLine(const std::string& line,
                                   const std::string& separator) {
  std::vector<std::string> vector_of_words;
  std::string::size_type start = 0;
  std::string::size_type end = line.find(separator, start);

  vector_of_words.push_back(line.substr(start, end));
  start = end + 1;
  vector_of_words.push_back(line.substr(start));

  return vector_of_words;
}

std::vector<Parsed_line> ParseFileIntoVector(const std::string& file_path,
                                             const std::string& separator) {
  std::ifstream file;
  std::string line;
  std::vector<Parsed_line> vector_of_lines;
  Parsed_line parsed_line;
  file.open(file_path);

  while (std::getline(file, line)) {
    std::vector<std::string> vector_of_words = ParseLine(line, separator);
    parsed_line.name = vector_of_words[0];
    parsed_line.surname = vector_of_words[1];
    vector_of_lines.push_back(parsed_line);
  }

  file.close();
  return vector_of_lines;
}

void WriteElementsIntoVector(
    const std::string& file_path,
    const std::vector<Parsed_line>& vector_of_parsed_lines) {
  std::ofstream file;

  file.open(file_path);

  if (file.is_open()) {
    for (const Parsed_line& element : vector_of_parsed_lines) {
      file << element.surname << std::endl;
    }
  } else {
    std::cout << "Couldn't open the file" << std::endl;
  }

  file.close();
}

// Функции--

int main() {
  std::string file_read_path = R"(C:\Projects\WorkWithFiles\FileRead.txt)";
  std::string file_write_path = R"(C:\Projects\WorkWithFiles\FileWrite.txt)";
  std::vector<Parsed_line> vector_of_lines =
      ParseFileIntoVector(file_read_path, "|");

  WriteElementsIntoVector(file_write_path, vector_of_lines);
}