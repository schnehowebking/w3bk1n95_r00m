# 🧠 w3bk1n9’s Final Boss: VM Reverse Engineering

**Difficulty:** Hard / Insane  
**Category:** Reverse Engineering  
**Platform:** Linux ELF  
**Author:** w3bk1n9  

---

## 📖 Overview

This challenge presents a stripped Linux ELF binary that validates user input using a **custom virtual machine (VM)**.  
There are **no direct string comparisons**, **no hashes**, and **no plaintext flags**.

Instead, user input is processed through a VM whose bytecode is **encrypted and decrypted at runtime**.  
The program validates input based solely on how it mutates internal state.

Brute force and simple patching will not work.

---

## 🧩 Initial Reconnaissance

```bash
file challenge
```

```bash
checksec --file=challenge
```

```bash
strings challenge
```

No readable flag strings are present.

---

## 🔍 Static Analysis

Using Ghidra reveals:
- Runtime-decrypted VM bytecode
- No direct comparisons
- State-based validation

---

## 🧪 Dynamic Analysis

```bash
gcc challenge.c -o challenge_dbg -O0 -g -fno-stack-protector -no-pie
gdb ./challenge_dbg
```

---

## ⚙️ VM Execution Logic

- Initial accumulator: `0x42`
- Runtime VM decryption
- State-based validation

---

## 🏁 Flag

```
thm{y0u_ar3_re4lly_pr0_a7_r3}
```

---

## 🏆 Credits

Created by **w3bk1n9** for TryHackMe.

---

## ⚠️ Disclaimer

Educational use only.
