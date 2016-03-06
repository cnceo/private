__author__ = 'vliu'
import os
import sys
from couchdb.couchdb import Connector as CouchBase

if __name__ == '__main__':
    print 'program start'
    db = CouchBase()
    db.connect('default', 'localhost', 8091)

    key = 'contact'
    doc = {'name': 'vic'}
    db.set(key, doc)
    val = db.get(key)
    print(val)
    stmt = 'SELECT fname, lname, age FROM default WHERE age > $age'
    param = 'age=2'
    result = db.query(stmt, param)
    print(result)
