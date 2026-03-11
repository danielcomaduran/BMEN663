# BMEN663
Repository for in-class demos for BMEN 663.
The repository is divided into multiple folders for each demo.

## Set-up instructions
- Folders starting with `embedded` should follow the [embeded programming instructions](#embedded-programing-instructions)
- Folders starting with `python` should follow the [python instructions](#python-instructions)


## [Python instructions](#python-instructions)
1. Install the latest version of [miniconda](https://docs.anaconda.com/miniconda/install/).
    1. Open the `miniconda terminal`, navigate to the path of this repository
    2. Run the following command to create and activate the working environment
    ```bash
    conda env create -f environment.yml
    conda activate bmen663
    ```
2. Install the latest version of [VS code](https://code.visualstudio.com/)
    1. Install the [Python](https://marketplace.visualstudio.com/items?itemName=ms-python.python) plugin
    2. Install the [Jupyter](https://marketplace.visualstudio.com/items?itemName=ms-toolsai.jupyter) plugin
3. In VS Code, open the folder of the repository (`Ctrl + K, Ctrl + O`)
    1. Open desired desired Jupyter Notebook
    2. Select the `bmen663` kernel at the top right of the Notebook
    3. Run the Jupyter Notebook section by section

    * Note that each section might have some settings variables at the begining of the code cell

## [Embedded programing instructions](#embedded-programing-instructions)
1. Install the latest [Arduino IDE 2](https://www.arduino.cc/en/software) version.
2. In Arduino IDE 2, open the desired folder (`Ctrl + O`) to debug, upload, and see the code output using the serial plotter.