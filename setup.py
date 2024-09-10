from setuptools import find_packages, setup

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
    package_dir={"": "Sources/Python"},
    classifiers=[
        "Programming Language :: Python :: 3",
        "Operating System :: OS Independent",
    ],
    python_requires=">=3.10",
    install_requires=[
        "pybind11",
    ],
    package_data={
        "OScofo": ["*.so"],
    },
    include_package_data=True,
    zip_safe=False,
)
