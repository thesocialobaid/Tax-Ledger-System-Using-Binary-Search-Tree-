# 🧾 Tax Ledger System (C++)

> **Developed by:** Muhammad Obaidullah (24L-0509)  
> **Course Project:** Data Structures and Algorithms  
> **Institution:** FAST-NUCES Lahore

---

## 📖 Overview

The **Tax Ledger System** is a C++ console-based application that efficiently manages taxpayer information using a **templated Binary Search Tree (BST)**.  
It allows for **insertion**, **deletion**, **searching**, and **display** of taxpayer data in multiple traversal orders.  

This project demonstrates:
- Use of **templates** in C++
- Implementation of a **generic Binary Search Tree**
- **Object-oriented programming** with encapsulated `TaxPayer` and `TaxLedgerSystem` classes
- Recursive algorithms for searching, inserting, and deleting nodes in BST
- Application of **data abstraction** and **dynamic memory management**

---

## 🧩 Features

✅ Register new taxpayers  
✅ Remove existing taxpayers  
✅ Search for taxpayers by ID  
✅ Display taxpayers using:
  - Inorder traversal (sorted by Tax ID)
  - Preorder traversal
  - Postorder traversal
  - Level order traversal  
✅ Count total and leaf nodes  
✅ Calculate tree height (depth)  
✅ Check if the tree is balanced  

---

## 🧠 Core Concepts Used

| Concept | Description |
|----------|-------------|
| **Templates** | Generic BST implementation supporting any data type |
| **OOP Principles** | Classes, encapsulation, constructors, operator overloading |
| **Recursion** | Implementing tree traversal and manipulation functions |
| **Dynamic Memory Allocation** | Creating and deleting BST nodes efficiently |
| **Data Structures** | Binary Search Tree as the core data structure |

---

## 🧱 Class Structure

### `class TaxPayer`
Represents an individual taxpayer.
```cpp
int taxId;
string name;
float taxAmountOwed;
