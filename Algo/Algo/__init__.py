from flask import *
from os import listdir
from os.path import isfile, isdir, join, expanduser, basename

app = Flask(__name__)

def make_tree(apath, spath):
    tree = dict(name=[spath, basename(spath)], children=[])
    try: lst = listdir(apath)
    except OSError:
        pass
    else:
        for name in lst:
            afn = join(apath, name)
            sfn = join(spath, name)
            if isdir(afn):
                tree['children'].append(make_tree(afn, sfn))
            else:
                tree['children'].append(dict(name=[sfn, name]))
    return tree

@app.route('/tree')
def dirtree():
    abspath = '/var/www/Algo/Algo/static/Algo_source'
    if __name__ == '__main__':
        abspath = './static/Algo_source'
    shortpath = '/static/Algo_source'
    return render_template('dirtree.html', tree=make_tree(abspath, shortpath))

@app.errorhandler(404)
def page_not_found(e):
    return render_template('404.html'), 404

@app.route('/')
def home():
    return render_template('home.html')

@app.route('/algo', defaults={'path': ''})
@app.route('/algo/<path:path>')
def algo(path):
    if path != '':
        if '.html' not in path:
            path += '.html'
        return render_template(path)

    return render_template('algo.html')

if __name__ == '__main__':
    app.debug = True
    app.run(host='0.0.0.0', port=5000)
