import os

# Folders to ignore
IGNORE_DIRS = {".git", ".vscode"}

def print_directory_structure(path, file, indent=""):
    try:
        items = sorted(os.listdir(path))
    except PermissionError:
        file.write(indent + "🚫 [Permission Denied]\n")
        return

    for index, item in enumerate(items):
        if item in IGNORE_DIRS:
            continue  # skip unwanted folders

        item_path = os.path.join(path, item)
        is_last = (index == len(items) - 1)

        # Tree-like structure
        connector = "└── " if is_last else "├── "
        file.write(indent + connector + item + "\n")

        if os.path.isdir(item_path):
            new_indent = indent + ("    " if is_last else "│   ")
            print_directory_structure(item_path, file, new_indent)


if __name__ == "__main__":
    root_dir = "E:/myWorkPlace/DSA"  # Change this to any path you want to scan

    output_file = "E:/myWorkPlace/DSA/docs/directory_structure.txt"
    with open(output_file, "w", encoding="utf-8") as f:
        f.write(f"Directory structure of: {os.path.abspath(root_dir)}\n\n")
        f.write("DSA\n")
        print_directory_structure(root_dir, f)

    print(f"✅ Directory structure saved to {output_file}")
