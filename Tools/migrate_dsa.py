import os
import shutil

# Source and destination directories
SRC = "E:\\myWorkPlace\\DSA"
DEST = "E:\\myWorkPlace\\DSA_clean"

# Map old folder names to new merged folder names
FOLDER_MAP = {
    "DivideConquer": "DivideAndConquer",
    "DivideAndConquer": "DivideAndConquer",
    "TwoPointer": "TwoPointers",
    "TwoPointers": "TwoPointers",
    "SortingAlgorithms": "Sorting",
    "Sorting": "Sorting"
}

# Folders to skip entirely
SKIP_DIRS = {".git", ".vscode", "build", "tests"}

def standardize_filename(filename, counter=None):
    """
    Converts a filename into the format: 01-problem_name.cpp
    If counter is provided, use it instead of extracting from filename
    """
    name, ext = os.path.splitext(filename)
    if ext != ".cpp":
        return filename  # only rename cpp files

    # Remove existing numbers if counter is provided
    parts = name.split("_")
    if counter is not None:
        new_name = f"{counter:02d}_{'_'.join(parts[1:]) if len(parts) > 1 else parts[0]}.cpp"
    else:
        new_name = filename
    return new_name

def migrate():
    if not os.path.exists(DEST):
        os.makedirs(DEST)

    readme_lines = []

    for root, dirs, files in os.walk(SRC):
        rel_path = os.path.relpath(root, SRC)

        # Skip unwanted folders
        if any(part in SKIP_DIRS or part.startswith(".") for part in rel_path.split(os.sep)):
            continue

        parts = rel_path.split(os.sep)

        # Preserve DP folder hierarchy exactly
        if parts[0] == "DP":
            clean_rel_path = os.path.join(*parts)
        else:
            # Map old folder names
            mapped_parts = [FOLDER_MAP.get(p, p) for p in parts]
            clean_rel_path = os.path.join(*mapped_parts) if rel_path != "." else ""

        dest_dir = os.path.join(DEST, clean_rel_path)
        os.makedirs(dest_dir, exist_ok=True)

        # Standardize cpp filenames
        cpp_counter = 1
        for f in files:
            if f.startswith(".") or f in ["directory_structure.py", "directory_structure.txt"]:
                continue

            if clean_rel_path.startswith("DP"):
                # Keep original DP filenames
                dest_file = os.path.join(dest_dir, f)
            else:
                new_name = standardize_filename(f, counter=cpp_counter)
                dest_file = os.path.join(dest_dir, new_name)
                cpp_counter += 1

            src_file = os.path.join(root, f)
            shutil.copy2(src_file, dest_file)
            readme_lines.append(os.path.join(clean_rel_path, os.path.basename(dest_file)))

    # Write README.md
    readme_path = os.path.join(DEST, "README.md")
    with open(readme_path, "w") as f:
        f.write("# Migrated DSA Repository\n\n")
        for line in readme_lines:
            f.write(f"- {line}\n")

    print(f"Migration complete! Check the new folder at {DEST}")

if __name__ == "__main__":
    migrate()
