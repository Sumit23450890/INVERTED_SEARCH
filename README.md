# INVERTED_SEARCH
📌 Project Overview

Inverted Search is a project that reads multiple text files, processes the words inside them, and creates a database where each word keeps a record of:
1.The files where it appears
2.How many times it appears in each file
3.This is useful for fast searching, indexing, and retrieval—similar to how search engines work.

📁 Features

1.Add multiple text files to a linked list
2.Create an inverted index (word → files + frequency)
3.Search for a word in the database
4.Display the complete database
5.Update the database by adding or removing files

🗂️ File Structure

INVERTED_SEARCH/
│── main.c
│── file.c
│── file.h
│── database.c
│── database.h
│── search.c
│── search.h
│── README.md

⚙️ How It Works

1. Add Files
The program adds filenames to a linked list.
2. Validate Files
Checks if the file exists and is not empty.
3. Create Database
Reads every file, extracts words, and stores them in a hash table.
4. Search Word
Search any word and get:
Frequency
File names where it appears
5. Display
Prints the entire inverted index.

🚀 How to Run

Open terminal inside the project folder:
gcc *.c -o inverted_search
./inverted_search

💡 Example Output

1. Create Database
2. Display Database
3. Search Word
4. Save Database
5. Exit
Enter your choice:

🛠️ Requirements

GCC Compiler
Linux/WSL recommended
Basic C programming knowledge

## 👨‍💻 Author

**Sumit Kumar Pradhan**
🔗 [GitHub](https://github.com/Sumit23450890)
🔗 [LinkedIn](https://www.linkedin.com/in/your-link/)

