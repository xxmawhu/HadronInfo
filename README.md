# HadronInfo
## Why
We can get all information from a track with a few lines. For example, 
we should write down 4 lines to get the momentum of one electron track
```c++
RecMdcKalTrack *mdcTrk = m_track->mdcKalTrack();
RecMdcKalTrack::setPidType(RecMdcKalTrack::electron);
double mass = 0.000511;
HepLorentzVector p4 = mdcTrk->p4(mass);
```
When we encounter a short-life particle, we must find its decay final tracks,
then add all information of them one by one together, sometime a `VertexFit` is
necessary, sometime not. At this case, we have to write down even more than 100
lines code, then debug to make sure the momentum is obtained properly.
However, it's both luck and terrible that we have many short-life particle, 
`Lambda`, `Ks` , `eta`, `phi`, `omega`,... 

This motevita us to create this package, `"Make people access to the short-life
particle easyly and reliably and save our life"`

## How
We find that the detector can only see `track` and `shower`, which like two 
stones building all visable particle. So we create two base class, named
`TrackInfo` and `ShowerInfo`, A series classes are inherited from them. Here
I give one example to show the relationship, `PionInfo` and `KaonInfo` are 
inherited from `TrackInfo`. Then a template named `CombInfo` is created to
create more classes. It seems like
```c++
template <class FirstInfo, class SecondInfo, int pid = 0,
          bool doVertexFit = false>
class CombInfo : public AvailableInfo {
   public:
   ...
   private:
   ...
};
```
Then we can build all others, for example
```c++
bool doVertexFit = true;
typedef CombInfo<ProtonInfo, PionInfo, 3312, doVertexFit> LamInfo;
typedef CombInfo<LamInfo, KaonInfo, 3334, doVertexFit> OmegamInfo;
```
It's cool! Is not it?

### the common method
One principle is that all class must pose some methods to providing
necessary information of the short-life particles. 

* GetName() 
        the name is important to show our respect to the particles.

* p4()
* mass()
...



## How
### usage
Create an instance is very easy. You can create one PionInfo instance
from the track,
```c++
...
PionInfo pionInfo(aTrack);
```
Also from a `CDCandidate`
```c++
...
PionInfo pionInfo(pionCandidate);
```
Nothing
```c++
PionInfo pionInfo();
```
But at this case, you must set the tracks before use it
```c++
pionInfo.setTrack(aTrack);
HepLorentzVector p4 = pionInfo.p4();
...
```


