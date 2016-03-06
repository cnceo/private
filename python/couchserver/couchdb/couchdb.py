__author__ = 'vliu'
from couchbase.bucket import Bucket
from couchbase.bucketmanager import BucketManager
from couchbase.n1ql import N1QLQuery

class Connector:
    def __init__(self):
        self.bucket = None

    def connect(self, bucketname, host, port=8091):
        url = "couchbase://" + host + ":" + str(port) + "/" + bucketname
        try:
            # bucket = Bucket('couchbases://10.1.1.1/default?certpath=/path/to/cluster/certificate.pem',password)
            bucket = Bucket(url)
            if bucket:
                print("connected" + url)
                self.bucket = bucket
        except Exception, e:
            print("error: " + str(e))
            # bm=BucketManager()

    def set(self, key, value):
        if self.bucket:
            self.bucket.upsert(key, value)

    def get(self, key):
        if self.bucket:
            v = self.bucket.get(key, quiet=True)
            return v.value
        return None

    def rm(self, key):
        if self.bucket:
            self.bucket.remove(key, quiet=True)

    def query(self, stmt, *param):
        if self.bucket:
            q = N1QLQuery(stmt, param)
            return self.bucket.n1ql_query(q)
        return None

    def close(self):
        #no need
        pass

    @classmethod
    def test(cls):
        print 'test'