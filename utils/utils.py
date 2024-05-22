def get_args():
    parser = argparse.ArgumentParser()
    parser.add_argument('-i', '--input')
    parser.add_argument('-o', '--output')
    parser.add_argument('-f', '--format')
    parser.add_argument('-v', dest='verbose', action='store_true')
    args = parser.parse_args()
    return(args)

def assign_paths(args):
    utils_folder=Path(os.path.dirname(os.path.abspath(__file__)))
    predvirushost_folder= utils_folder.parent.absolute()
    user_folder = os. getcwd()
    user_output_folder = os.path.join(user_folder, args.output)
    return utils_folder, predvirushost_folder, user_folder, user_output_folder