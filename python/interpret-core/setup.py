# Copyright (c) 2019 Microsoft Corporation
# Distributed under the MIT software license

from setuptools import setup, find_packages

name = "interpret-core"
version = "0.1.16-prerelease"
long_description = """
Core system for **the** interpret package.

https://github.com/microsoft/interpret
"""

entry_points = {
    "interpret_ext_blackbox": [
        "BlackboxExplainerExample = interpret.ext.blackbox.example_blackbox_explainer_ext:ExampleExplainer"
    ],
    "interpret_ext_provider": [
        "ExampleVisualizeProvider = interpret.ext.provider.example_provider:ExampleVisualizeProvider"
    ],
}
package_data = {
    "interpret": [
        "lib/lib_ebmcore_win_x64.dll",
        "lib/lib_ebmcore_linux_x64.so",
        "lib/lib_ebmcore_mac_x64.dylib",
        "lib/lib_ebmcore_win_x64_debug.dll",
        "lib/lib_ebmcore_linux_x64_debug.so",
        "lib/lib_ebmcore_mac_x64_debug.dylib",
        "lib/lib_ebmcore_win_x64.pdb",
        "lib/lib_ebmcore_win_x64_debug.pdb",
        "visual/assets/udash.css",
        "visual/assets/udash.js",
        "visual/assets/favicon.ico",
        "pytest.ini",
    ]
}
sklearn_dep = "scikit-learn>=0.20.0"
extras = {
    # Core
    "required": ["numpy>=1.15.1", "scipy>=1.2.1", "pandas>=0.24.0"],
    "debug": ["psutil>=5.6.2"],
    "notebook": ["ipykernel>=5.1.0", "ipython>=7.4.0"],
    # Plotly (required if .visualize is ever called)
    "plotly": ["plotly>=3.8.1"],
    # Explainers
    "lime": ["lime>=0.1.1.33"],
    "sensitivity": ["SALib>=1.3.3"],
    "shap": ["shap>=0.28.5", "dill"],
    "ebm": [sklearn_dep],
    "linear": [sklearn_dep],
    "decisiontree": [sklearn_dep],
    "skoperules": ["skope-rules>=1.0.0"],
    # Dash
    "dash": [
        "dash>=1.0.0",
        "dash-cytoscape>=0.1.1",
        "dash-table>=4.1.0" "gevent>=1.3.6",
        "requests>=2.19.0",
    ],
    # Testing
    "testing": [
        "pytest>=4.3.0",
        "pytest-runner>=4.4",
        "pytest-xdist>=1.29",
        "nbconvert>=5.4.1",
        "selenium>=3.141.0",
        "pytest-cov>=2.6.1",
        "flake8>=3.7.7",
        "jupyter>=1.0.0",
        "ipywidgets>=7.4.2",
    ],
}

setup(
    name=name,
    version=version,
    author="InterpretML Team",
    author_email="interpret@microsoft.com",
    description="Fit interpretable models. Explain blackbox machine learning.",
    long_description=long_description,
    long_description_content_type="text/markdown",
    url="https://github.com/microsoft/interpret",
    packages=find_packages(),
    package_data=package_data,
    classifiers=[
        "Programming Language :: Python :: 3.5",
        "Programming Language :: Python :: 3.6",
        "Programming Language :: Python :: 3.7",
        "Development Status :: 3 - Alpha",
        "License :: OSI Approved :: MIT License",
        "Operating System :: OS Independent",
    ],
    extras_require=extras,
    entry_points=entry_points,
    install_requires=[],
)
