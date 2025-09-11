import os
import re
import shutil

# Root directory
ROOT = "E:/myWorkPlace/DSA"

# Future folders to ensure existence
FOLDERS = [
    "Arrays/BinarySearch",
    "Arrays/DivideAndConquer",
    "Arrays/SlidingWindow",
    "Arrays/Sorting",
    "Arrays/TwoPointers",
    "BitManipulation",
    "DP/01-0_1_knapsack",
    "DP/02-unbounded_knapsack",
    "Heap",
    "Graphs",
    "Trees",
    "Strings",
    "Greedy",
    "Math",
    "tests",
    "docs",
    "build",
]

# Create folders if missing
for folder in FOLDERS:
    os.makedirs(os.path.join(ROOT, folder), exist_ok=True)

# 🔧 Helper: standardize filenames to 01-problem_name.cpp
def standardize_filename(idx, filename):
    name, ext = os.path.splitext(filename)
    if ext != ".cpp":
        return None
    # Replace spaces, dashes with underscores
    name = name.replace("-", "_").replace(" ", "_")
    # Convert CamelCase → snake_case
    name = re.sub(r'([a-z0-9])([A-Z])', r'\1_\2', name).lower()
    return f"{idx:02d}-{name}.cpp"

# Remove .exe files
for dirpath, _, files in os.walk(ROOT):
    for file in files:
        if file.endswith(".exe"):
            os.remove(os.path.join(dirpath, file))
            print(f"🗑 Removed binary: {os.path.join(dirpath, file)}")

# Rename .cpp files
for dirpath, _, files in os.walk(ROOT):
    cpp_files = [f for f in files if f.endswith(".cpp")]
    cpp_files.sort()
    for idx, file in enumerate(cpp_files, 1):
        old_path = os.path.join(dirpath, file)
        new_name = standardize_filename(idx, file)
        if new_name:
            new_path = os.path.join(dirpath, new_name)
            if old_path != new_path:
                print(f"📂 Renaming: {file} → {new_name}")
                shutil.move(old_path, new_path)

# Create .gitignore
gitignore_path = os.path.join(ROOT, ".gitignore")
with open(gitignore_path, "w") as f:
    f.write("""# Ignore binaries
*.exe
*.out
*.o
/build/
""")

# 🔧 Generate README.md
def generate_readme():
    lines = []
    lines.append("# 🧑‍💻 DSA Practice Repository\n")
    lines.append("A structured collection of **Data Structures & Algorithms problems** implemented in C++.\n")
    lines.append("---\n")
    lines.append("## 📂 Folder Structure\n")

    for category in sorted(os.listdir(ROOT)):
        category_path = os.path.join(ROOT, category)
        if not os.path.isdir(category_path) or category in ["tests", "docs", "build"]:
            continue

        lines.append(f"### 🔹 {category}\n")

        for subdir, _, files in os.walk(category_path):
            relative_path = os.path.relpath(subdir, ROOT)
            if subdir != category_path:
                lines.append(f"- **{os.path.basename(subdir)}**")

            for file in sorted(files):
                if file.endswith(".cpp"):
                    problem_name = file[3:].replace("_", " ").replace(".cpp", "")
                    link = os.path.join(relative_path, file).replace("\\", "/")
                    if subdir == category_path:
                        lines.append(f"  - [{problem_name}]({link})")
                    else:
                        lines.append(f"    - [{problem_name}]({link})")
        lines.append("")

    return "\n".join(lines)

readme_path = os.path.join(ROOT, "README.md")
with open(readme_path, "w", encoding="utf-8") as f:
    f.write(generate_readme())

print("✅ Repo restructuring complete — files renamed + README.md generated!")
