from flask import *
from os import listdir
from os.path import isfile, isdir, join, expanduser, basename

app = Flask(__name__)

def make_tree(path):
    tree = dict(name=[path, basename(path)], children=[])
    try: lst = listdir(path)
    except OSError:
        pass
    else:
        for name in lst:
            fn = join(path, name)
            if isdir(fn):
                tree['children'].append(make_tree(fn))
            else:
                tree['children'].append(dict(name=[fn, name]))
    return tree

# def make_tree(path):
#     tree = dict(name=os.path.basename(path), children=[])
#     try: lst = os.listdir(path)
#     except OSError:
#         pass #ignore errors
#     else:
#         for name in lst:
#             fn = os.path.join(path, name)
#             if os.path.isdir(fn):
#                 tree['children'].append(make_tree(fn))
#             else:
#                 tree['children'].append(dict(name=name))
#     return tree

@app.route('/tree')
def dirtree():
    path = expanduser(u'./static/Algo_source')
    return render_template('dirtree.html', tree=make_tree(path))

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
