from setuptools import setup, find_packages
import os

# Get all .so files in the package directory
libs = [
    os.path.basename(x)
    for x in os.listdir("./Sources/Python/OScofo")
    if x.endswith(".so")
]

if not libs:
    raise RuntimeError(
        "No shared libraries found in Sources/Python/OScofo, please use cmake first"
    )

setup(
    name="OScofo",
    version="0.1.0",
    author="Charles K. Neimog",
    author_email="charlesneimog@outlook.com",
    description="",
    long_description=open("README.md").read(),
    long_description_content_type="text/markdown",
    url="https://github.com/charlesneimog/OScofo",
    packages=find_packages(where="Sources/Python"),
    package_dir={"OScofo": "Sources/Python/OScofo"},
    package_data={"OScofo": libs},
    include_package_data=True,
    zip_safe=False,
)
