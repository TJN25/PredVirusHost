from setuptools import setup

setup(
    package_dir = {"": "src"},
    scripts=['src/predvirushost/run_predvirushost.py'],
        # entry_points={
        # 'console_scripts': [
        #     'predvirushost = predvirushost:run_predvirushost',
        # ]},
    name = 'predvirushost',
    version='0.2.0',
    description='Predicts the host domain of contigs from viromes by comparing proteins from a number of contigs to hmm models and then scores each contig based on similarity to those models.',
    url='https://github.com/TJN25/PredVirusHost',
    author='Thomas J. Nicholson',
    author_email='nicholson.tom.n@gmail.com',
    license='MIT',
    packages=['predvirushost', 'predvirushost.utils'],
    classifiers=[
        'Development Status :: 3 - Alpha',
        'Programming Language :: Python :: 3',
        'Programming Language :: Python :: 3.12',
        'Operating System :: OS Independent',
        'License :: OSI Approved :: GNU General Public License v3 or later (GPLv3+)'
    ]



)
