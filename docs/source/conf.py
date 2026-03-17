# Configuration file for the Sphinx documentation builder.
#
# For the full list of built-in configuration values, see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Project information -----------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#project-information

#import sphinx_rtd_theme

project = 'iw1x-server'
#copyright = '2025, ...'
author = 'Raphael'
release = 'latest'

# -- General configuration ---------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#general-configuration

extensions = [
    'sphinx_copybutton',
    'sphinx_nefertiti',
    'sphinx.ext.autosectionlabel',
]

templates_path = ['_templates']
exclude_patterns = []

# -- Options for HTML output -------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#options-for-html-output

#html_theme = "piccolo_theme"
#html_permalinks_icon = '<span>#</span>'
html_theme = 'sphinx_nefertiti'


html_static_path = ['_static']
html_css_files = ["copybutton.css"]

html_sidebars = {'**': ['globaltoc.html']}
html_theme_options = {
    'style': 'purple',
    'repository_url': 'https://gitlab.com/kazam0180/iw1x-server',
    'repository_name': 'iw1x-server',
    'pygments_dark_style': 'dracula'
}
