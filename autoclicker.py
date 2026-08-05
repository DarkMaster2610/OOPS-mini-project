import os
import subprocess
from PIL import Image, ImageDraw, ImageFont

# ==========================
# CONFIGURE THIS
# ==========================

JAVA_FOLDER = r"C:\Users\Admin\Desktop\11249A016_Java lab"

FONT_SIZE = 18
PADDING = 20

try:
    FONT = ImageFont.truetype("consola.ttf", FONT_SIZE)
except:
    FONT = ImageFont.load_default()


# ==========================
# CREATE TERMINAL IMAGE
# ==========================

def save_terminal(text, filename):

    lines = text.splitlines()

    dummy = Image.new("RGB", (1, 1))
    draw = ImageDraw.Draw(dummy)

    width = 0

    for line in lines:
        bbox = draw.textbbox((0, 0), line, font=FONT)
        width = max(width, bbox[2])

    line_height = draw.textbbox((0, 0), "Ag", font=FONT)[3] + 6

    img = Image.new(
        "RGB",
        (width + 2 * PADDING, line_height * len(lines) + 2 * PADDING),
        (12, 12, 12),
    )

    draw = ImageDraw.Draw(img)

    y = PADDING

    for line in lines:
        draw.text((PADDING, y), line, fill=(230, 230, 230), font=FONT)
        y += line_height

    img.save(filename)


# ==========================
# MAIN
# ==========================

os.chdir(JAVA_FOLDER)

java_files = [f for f in os.listdir() if f.endswith(".java")]

for file in java_files:

    classname = file[:-5]

    print(f"\nCompiling {file}")

    compile_result = subprocess.run(
        ["javac", file],
        capture_output=True,
        text=True
    )

    if compile_result.returncode != 0:
        print("Compilation failed.")
        print(compile_result.stderr)
        continue

    print(f"Running {classname}...")

    try:
        run = subprocess.run(
            ["java", classname],
            capture_output=True,
            text=True,
            timeout=1
        )

        output = run.stdout + run.stderr

    except subprocess.TimeoutExpired:

        print(f"{classname} is waiting for input.")
        print("Opening interactive console...")

        os.system(f'start cmd /k "cd /d {JAVA_FOLDER} && java {classname}"')

        input("Finish the program and close CMD.\nPress ENTER here...")

        output = "<Interactive program executed manually>"

    text = (
        f"PS {JAVA_FOLDER}> javac {file}\n\n"
        f"PS {JAVA_FOLDER}> java {classname}\n\n"
        f"{output}"
    )

    save_terminal(text, classname + ".png")

    print(f"Saved {classname}.png")

print("\nDone.")