# census - Midterm 1: Large Datasets Processing in C++

## Video defense

[https://eafit-my.sharepoint.com/:v:/g/personal/…](https://eafit-my.sharepoint.com/:v:/g/personal/lmtorresv_eafit_edu_co/EUr-95lBOAtGrd6QeXESGZUBA-p4nDP4QLcuFmUQsTqMMA?e=U42gi7&nav=eyJyZWZlcnJhbEluZm8iOnsicmVmZXJyYWxBcHAiOiJTdHJlYW1XZWJBcHAiLCJyZWZlcnJhbFZpZXciOiJTaGFyZURpYWxvZy1MaW5rIiwicmVmZXJyYWxBcHBQbGF0Zm9ybSI6IldlYiIsInJlZmVycmFsTW9kZSI6InZpZXcifX0%3D)

## Context (taken from the report)

This project focuses on handling large datasets in C/C++ on Linux and evaluating
how different design choices affect performance. The main objectives are:

- Generate and process datasets with millions of records.
- Compare using values vs. pointers to measure memory savings and runtime
  performance.
- Compare using structs (C) vs. classes (C++) to examine efficiency and memory
  layout.
- Record execution time and memory usage for each query with a custom monitor.
Each record contains: full name, date of birth, city of residence, assets,
debts, ID number, and the assigned tax calendar group (A/B/C) based on the last
digits of the ID.
