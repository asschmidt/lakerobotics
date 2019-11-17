'''
Created on 21.06.2019

@author: Andreas
'''
from jinja2 import Environment, Template, FileSystemLoader

env = Environment(
    loader=FileSystemLoader('./'),
    trim_blocks = True,
    lstrip_blocks = True
    )

ctx = {'nodeName' : 'My Value for this'}

template = env.get_template('node_header.template')
print(template.render(ctx))