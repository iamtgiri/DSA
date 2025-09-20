
import os
from datetime import datetime

# ---------------- CONFIG ----------------
DSA_PATH = r"E:\myWorkPlace\DSA"  # path to your repo
README_FILE = os.path.join(DSA_PATH, "README.md")

# Track total + per-category counts
TOTAL_PROBLEMS = 0
CATEGORY_COUNTS = {}

# Algorithm categories (top-level folders)
CATEGORIES = [
    "Arrays",
    "BitManipulation",
    "DP",
    "Graphs",
    "Greedy",
    "Heap",
    # "Math",
    "Strings",
    "Trees"
]

# ---------------- FUNCTIONS ----------------
def create_title(name):
    """Converts folder/file names to title case for markdown headers."""
    return name.replace(".cpp","").replace("_", " ").title()

def render_progress_bar(count, max_count, length=20):
    """Renders a text-based progress bar."""
    filled = int(length * count / max_count) if max_count > 0 else 0
    empty = length - filled
    return "█" * filled + "░" * empty


def generate_file_list(category, category_path, relative_path=""):
    """
    Recursively generates a markdown list of files in the folder.
    Returns a string in markdown format.
    """
    global TOTAL_PROBLEMS, CATEGORY_COUNTS
    md = ""
    entries = sorted(os.listdir(category_path))
    for entry in entries:
        full_path = os.path.join(category_path, entry)
        if os.path.isdir(full_path):
            md += f"\n#### 📂 {create_title(entry)}\n\n"
            md += generate_file_list(category, full_path, os.path.join(relative_path, entry))
        elif entry.endswith(".cpp"):
            TOTAL_PROBLEMS += 1
            CATEGORY_COUNTS[category] = CATEGORY_COUNTS.get(category, 0) + 1
            # Relative path for hyperlink
            file_link = os.path.join(relative_path, entry).replace("\\", "/")
            md += f"- [{create_title(entry)}]({file_link})\n"
    return md

def generate_readme():
    now = datetime.now().strftime("%d-%m-%Y %H:%M")

    # Header with badges
    content = f"<h4 align=\"center\">Last Updated: {now}</h4>\n\n"
    content += "<h1 align=\"center\">Data Structures and Algorithms (DSA)</h1>\n\n"
    content += """
<p align="center"> 
  <!-- 🔹 Core repo info -->
  <img src="https://img.shields.io/github/repo-size/iamtgiri/DSA?style=for-the-badge" />
  <img src="https://img.shields.io/github/languages/top/iamtgiri/DSA?style=for-the-badge" />
  <img src="https://img.shields.io/github/last-commit/iamtgiri/DSA?style=for-the-badge" />
  <img src="https://img.shields.io/github/license/iamtgiri/DSA?style=for-the-badge" />
</p>

<p align="center"> 
  <!-- 🔹 Social + Fun -->
  <img src="https://img.shields.io/github/stars/iamtgiri/DSA?style=for-the-badge" />
  <img src="https://img.shields.io/github/forks/iamtgiri/DSA?style=for-the-badge" />
  <img src="https://img.shields.io/github/contributors/iamtgiri/DSA?style=for-the-badge" />
  <img src="https://img.shields.io/badge/DSA-Practice-purple?style=for-the-badge" />
  <img src="https://img.shields.io/badge/Keep-Coding-blue?style=for-the-badge" />
  <img src="https://img.shields.io/badge/Learning-In%20Progress-green?style=for-the-badge" />
</p>


This repository contains my practice code for **Data Structures and Algorithms (DSA)**. It includes solutions to common problems, algorithm implementations, and coding exercises to sharpen problem-solving skills.

---
"""

    # Navigation Index
    content += "## 📂 Categories\n"
    for category in CATEGORIES:
        if os.path.exists(os.path.join(DSA_PATH, category)):
            content += f"- [{category}](#-{category.lower()})\n"
    content += "\n---\n"

    # Problems List with collapsible sections
    content += "## ※ Problems List\n"
    for category in CATEGORIES:
        category_path = os.path.join(DSA_PATH, category)
        if not os.path.exists(category_path):
            continue

        content += f"\n## ■ {category}\n"
        content += f"<details>\n  <summary>Click to expand</summary>\n\n"
        content += generate_file_list(category, category_path, category)
        content += "\n</details>\n"

    # Summary Section
    content += """
---

## 📊 Summary
"""
    if CATEGORY_COUNTS:
        max_count = max(CATEGORY_COUNTS.values())
        for category, count in CATEGORY_COUNTS.items():
            bar = render_progress_bar(count, max_count)
            content += f"- **{category}**: {count} problems  \n  `{bar}`\n"
    content += f"\n- **Total Problems Solved:** {TOTAL_PROBLEMS}\n"
    # for category, count in CATEGORY_COUNTS.items():
    #     content += f"- **{category}**: {count} problems\n"
    # content += f"\n- **Total Problems Solved:** {TOTAL_PROBLEMS}\n"

    # Footer
    footer = """
---


## ※ Contributing

This repository is primarily for personal practice, but contributions are always welcome!
Feel free to open issues or submit pull requests with improvements, suggestions or new problem solutions.

"""
    content += footer

    # Write to README.md
    with open(README_FILE, "w", encoding="utf-8") as f:
        f.write(content)
    print(f"README.md generated successfully at {README_FILE}")

if __name__ == "__main__":
    generate_readme()

