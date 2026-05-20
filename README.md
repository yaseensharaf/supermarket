<div align="center">

<img src="https://img.shields.io/badge/Language-C++-00599C?style=for-the-badge&logo=cplusplus&logoColor=white"/>
<img src="https://img.shields.io/badge/Storage-File%20I%2FO-gray?style=for-the-badge&logo=files&logoColor=white"/>
<img src="https://img.shields.io/badge/Interface-CLI-black?style=for-the-badge&logo=windowsterminal&logoColor=white"/>
<img src="https://img.shields.io/badge/Platform-Cross--Platform-brightgreen?style=for-the-badge"/>
<img src="https://img.shields.io/badge/Status-Complete-success?style=for-the-badge"/>

<br/><br/>

# Market Inventory Management System

### A command-line C++ application for managing product inventory with persistent file-based storage

<br/>

</div>

---

## Table of Contents

1. [Overview](#-overview)
2. [Features](#-features)
3. [Data Structure](#-data-structure)
4. [Getting Started](#-getting-started)
5. [Usage](#-usage)
6. [File Storage](#-file-storage)
7. [Function Reference](#-function-reference)
8. [Known Limitations & Future Work](#-known-limitations--future-work)
9. [Developer](#-developer)

---

## 🌟 Overview

The **Market Inventory Management System** is a console-based C++ application that allows users to manage a product inventory database through a simple interactive menu. All data is persisted to a local text file (`market.txt`), making it lightweight and dependency-free — no database engine or external libraries required.

The system supports the full product lifecycle: adding new items, editing existing records, deleting items, searching by name, and monitoring expiry dates to help identify stock that needs attention.

---

## ✨ Features

| Feature | Description |
|---|---|
| ➕ **Add Item** | Register a new product with name, expiry date, quantity, price, and type |
| ✏️ **Edit Item** | Search for an existing item by name and overwrite it with updated details |
| 🗑️ **Delete Item** | Remove a product from the database by name |
| 🔍 **Search Item** | Find and display any product record by keyword |
| ⏰ **Expiry Checker** | Scan all items and report which products have expired or are still valid |
| 💾 **Persistent Storage** | All records are automatically saved to `market.txt` after every operation |
| 🧹 **Auto Cleanup** | Empty lines are automatically removed from the database file after edits |
| 📋 **Live Display** | The full product list is printed to the terminal after every create, edit, or delete action |

---

## 🗂️ Data Structure

Each product record is represented by the following `struct`:

```cpp
struct Product {
    std::string name;          // Product name
    std::string expiry_date;   // Expiry date in MM/DD/YYYY format
    int         quantity;      // Stock quantity
    float       price;         // Unit price
    std::string type;          // Product category/type
};
```

Records are stored in `market.txt` as tab-separated values, one product per line:

```
ProductName    MM/DD/YYYY    Quantity    Price    Type
```

**Example:**
```
Milk           12/31/2025    50          1.99     Dairy
Bread          11/15/2025    30          2.49     Bakery
Apples         01/20/2026    100         0.99     Produce
```

---

## 🚀 Getting Started

### Prerequisites

| Tool | Requirement |
|---|---|
| C++ Compiler | GCC (g++) 7+ · Clang 6+ · MSVC 2017+ |
| C++ Standard | C++11 or later |
| OS | Windows · macOS · Linux |

### Compile

**Using g++ (Linux / macOS / Windows with MinGW):**
```bash
g++ -std=c++11 -o market main.cpp
```

**Using Clang:**
```bash
clang++ -std=c++11 -o market main.cpp
```

**Using MSVC (Windows):**
```bash
cl /EHsc /std:c++11 main.cpp /Fe:market.exe
```

### Run

```bash
# Linux / macOS
./market

# Windows
market.exe
```

> ⚠️ **Note:** The program reads and writes `market.txt` in the **same directory** as the executable. Make sure you run the program from the correct working directory.

---

## 📖 Usage

On launch, the program immediately prints the current contents of `market.txt`, then displays the main menu:

```
1-Create Item
2-Edit Item
3-Delete Item
4-search Item
5-Items about to expire
6-Exit and Save to Text
==========================
Select option>>
```

---

### Option 1 — Create Item

Prompts for all five product fields and appends the new record to `market.txt`:

```
Item name: Milk
Expire date: 12/31/2025
Item quantity: 50
price: 1.99
item Type: Dairy
```

The updated inventory is printed immediately after the item is added.

---

### Option 2 — Edit Item

Prompts for the name of the item to edit. The existing record is removed, and you are prompted to re-enter all fields with updated values:

```
What Item u want to edit: Milk

Enter the product name: Milk
Enter the date: 06/30/2026
Enter the quantity: 75
Enter the price: 2.19
Enter the type: Dairy
```

---

### Option 3 — Delete Item

Prompts for the item name and removes all matching lines from `market.txt`:

```
Enter the name of the item to delete: Bread
```

The updated inventory is printed after deletion.

---

### Option 4 — Search Item

Prompts for a keyword and prints any line in `market.txt` that contains a match (case-sensitive):

```
Enter the name of the item to search for: Milk
Milk    12/31/2025    50    1.99    Dairy
```

---

### Option 5 — Items About to Expire

Reads all records and compares each expiry date against the current system date. Prints a status line for every product:

```
Milk expires on 12/31/2025
Bread has expired
Apples expires on 01/20/2026
```

---

### Option 6 — Exit

Exits the loop and terminates the program. All data is already persisted in `market.txt` from previous operations.

```
Exit...Saving to file!
```

---

## 💾 File Storage

The system uses a plain text file `market.txt` as its database. Every operation reads from and writes to this file directly.

| Operation | File Behaviour |
|---|---|
| **Add** | New record appended with `std::ios::app` |
| **Edit** | Entire file rewritten with the target record replaced |
| **Delete** | Entire file rewritten with matching lines excluded |
| **Search** | File read-only; no modifications made |
| **Expiry check** | File read-only; no modifications made |
| **Empty line cleanup** | File rewritten with blank lines stripped after every write |

> The file is created automatically on first run if it does not exist.

---

## 🔧 Function Reference

| Function | Signature | Description |
|---|---|---|
| `print` | `int print()` | Reads `market.txt` and prints all records to stdout |
| `delete_empty_line` | `void delete_empty_line()` | Rewrites `market.txt` with all blank lines removed |
| `items_about_to_expire` | `void items_about_to_expire()` | Compares each product's expiry date to today and reports status |
| `AddItem` | `void AddItem()` | Prompts for product details and appends a new record to the file |
| `editItem` | `void editItem()` | Finds a product by name, removes it, and rewrites it with updated values |
| `search` | `void search()` | Searches for a keyword across all lines and prints any matches |
| `Delete` | `void Delete()` | Removes all lines containing the given product name |
| `main` | `int main()` | Entry point — displays menu and routes input to the correct function |

---

## ⚠️ Known Limitations & Future Work

### Current Limitations

| Area | Limitation |
|---|---|
| **Search** | Case-sensitive — searching `milk` will not find `Milk` |
| **Edit** | Finds by exact name match; partial names will not work |
| **Expiry parsing** | Relies on `en_US.utf-8` locale — may behave differently on non-English systems |
| **Capacity** | In-memory arrays are capped at `maxrow = 10`; file storage is unlimited but arrays will not reflect more than 10 items |
| **No input validation** | Non-numeric input for quantity or price fields will cause undefined behaviour |
| **Concurrency** | No file locking — simultaneous access from multiple processes could corrupt data |

### Proposed Future Enhancements

- **Case-insensitive search** — convert both input and stored names to lowercase before comparison
- **Input validation** — check that quantity is a positive integer and price is a valid float before writing
- **Low stock alerts** — flag products whose quantity falls below a configurable threshold
- **Sort and filter** — sort listings by name, price, quantity, or expiry date
- **CSV export** — export inventory to a properly formatted CSV for use in spreadsheet tools
- **SQLite integration** — replace flat-file storage with an embedded database for concurrent access and faster querying

---

## 👨‍💻 Developer

**Yaseen Sharaf**

[![GitHub](https://img.shields.io/badge/GitHub-yaseensharaf-181717?style=for-the-badge&logo=github&logoColor=white)](https://github.com/yaseensharaf)

---

## 📄 License

```
Copyright © Yaseen Sharaf. All rights reserved.
```
