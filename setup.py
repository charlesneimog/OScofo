from setuptools import setup, find_packages
import os
import re


def get_version_from_header(file):
    version = {}
    with open(file, "r") as f:
        for line in f:
            match = re.match(r"#define\s+(\w+)\s+(\d+)", line)
            if match:
                name, value = match.groups()
                version[name] = value
    return version


version = get_version_from_header("Sources/OScofo.hpp")

major = version["OSCOFO_VERSION_MAJOR"]
minor = version["OSCOFO_VERSION_MINOR"]
patch = version["OSCOFO_VERSION_PATCH"]

version_string = f"{major}.{minor}.{patch}"


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
    version=version_string,
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
